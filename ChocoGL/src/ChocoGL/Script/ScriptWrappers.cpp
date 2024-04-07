#include "clpch.h"
#include "ScriptWrappers.h"

#include "ChocoGL/Core/Math/Noise.h"

#include "ChocoGL/Scene/Scene.h"
#include "ChocoGL/Scene/Entity.h"
#include "ChocoGL/Scene/Components.h"

#include <box2d/box2d.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ChocoGL/Core/Input.h"
#include <mono/jit/jit.h>

namespace ChocoGL {
	extern std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	extern std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;
}

namespace ChocoGL { namespace Script {

	enum class ComponentID
	{
		None = 0,
		Transform = 1,
		Mesh = 2,
		Script = 3,
		SpriteRenderer = 4
	};



	////////////////////////////////////////////////////////////////
	// Math ////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	float ChocoGL_Noise_PerlinNoise(float x, float y)
	{
		return Noise::PerlinNoise(x, y);
	}

	static std::tuple<glm::vec3, glm::quat, glm::vec3> GetTransformDecomposition(const glm::mat4& transform)
	{
		glm::vec3 scale, translation, skew;
		glm::vec4 perspective;
		glm::quat orientation;
		glm::decompose(transform, scale, orientation, translation, skew, perspective);

		return { translation, orientation, scale };
	}

	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	// Input ///////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	bool ChocoGL_Input_IsKeyPressed(KeyCode key)
	{
		return Input::IsKeyPressed(key);
	}

	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	// Entity //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	void ChocoGL_Entity_GetTransform(uint64_t entityID, glm::mat4* outTransform)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		memcpy(outTransform, glm::value_ptr(transformComponent.Transform), sizeof(glm::mat4));
	}

	void ChocoGL_Entity_SetTransform(uint64_t entityID, glm::mat4* inTransform)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		memcpy(glm::value_ptr(transformComponent.Transform), inTransform, sizeof(glm::mat4));
	}

	void ChocoGL_Entity_GetForwardDirection(uint64_t entityID, glm::vec3* outForward)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& transformComponent = entity.GetComponent<TransformComponent>();

		auto [position, rotation, scale] = GetTransformDecomposition(transformComponent.Transform);
		*outForward = glm::rotate(glm::inverse(glm::normalize(rotation)), glm::vec3(0, 0, -1));
	}

	void ChocoGL_Entity_GetRightDirection(uint64_t entityID, glm::vec3* outRight)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& transformComponent = entity.GetComponent<TransformComponent>();

		auto [position, rotation, scale] = GetTransformDecomposition(transformComponent.Transform);
		*outRight = glm::rotate(glm::inverse(glm::normalize(rotation)), glm::vec3(1, 0, 0));
	}

	void ChocoGL_Entity_GetUpDirection(uint64_t entityID, glm::vec3* outUp)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& transformComponent = entity.GetComponent<TransformComponent>();

		auto [position, rotation, scale] = GetTransformDecomposition(transformComponent.Transform);
		*outUp = glm::rotate(glm::inverse(glm::normalize(rotation)), glm::vec3(0, 1, 0));
	}

	void ChocoGL_Entity_CreateComponent(uint64_t entityID, void* type)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		s_CreateComponentFuncs[monoType](entity);
	}

	bool ChocoGL_Entity_HasComponent(uint64_t entityID, void* type)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
		bool result = s_HasComponentFuncs[monoType](entity);
		return result;
	}

	uint64_t ChocoGL_Entity_FindEntityByTag(MonoString* tag)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");

		Entity entity = scene->FindEntityByTag(mono_string_to_utf8(tag));
		if (entity)
			return entity.GetComponent<IDComponent>().ID;

		return 0;
	}

	void* ChocoGL_MeshComponent_GetMesh(uint64_t entityID)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& meshComponent = entity.GetComponent<MeshComponent>();
		return new Ref<Mesh>(meshComponent.Mesh);
	}

	void ChocoGL_MeshComponent_SetMesh(uint64_t entityID, Ref<Mesh>* inMesh)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		auto& meshComponent = entity.GetComponent<MeshComponent>();
		meshComponent.Mesh = inMesh ? *inMesh : nullptr;
	}

	void ChocoGL_RigidBody2DComponent_ApplyLinearImpulse(uint64_t entityID, glm::vec2* impulse, glm::vec2* offset, bool wake)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
		auto& component = entity.GetComponent<RigidBody2DComponent>();
		b2Body* body = (b2Body*)component.RuntimeBody;
		body->ApplyLinearImpulse(*(const b2Vec2*)impulse, body->GetWorldCenter() + *(const b2Vec2*)offset, wake);
	}

	void ChocoGL_RigidBody2DComponent_GetLinearVelocity(uint64_t entityID, glm::vec2* outVelocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
		auto& component = entity.GetComponent<RigidBody2DComponent>();
		b2Body* body = (b2Body*)component.RuntimeBody;
		const auto& velocity = body->GetLinearVelocity();
		CL_CORE_ASSERT(outVelocity);
		*outVelocity = { velocity.x, velocity.y };
	}

	void ChocoGL_RigidBody2DComponent_SetLinearVelocity(uint64_t entityID, glm::vec2* velocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBody2DComponent>());
		auto& component = entity.GetComponent<RigidBody2DComponent>();
		b2Body* body = (b2Body*)component.RuntimeBody;
		CL_CORE_ASSERT(velocity);
		body->SetLinearVelocity({ velocity->x, velocity->y });
	}

	void ChocoGL_RigidBodyComponent_AddForce(uint64_t entityID, glm::vec3* force, ForceMode forceMode)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		physx::PxRigidActor* actor = (physx::PxRigidActor*)component.RuntimeActor;
		physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();

		// We don't want to assert since scripts might want to be able to switch
		// between a static and dynamic actor at runtime
		if (!dynamicActor)
			return;

		CL_CORE_ASSERT(force);
		dynamicActor->addForce({ force->x, force->y, force->z }, (physx::PxForceMode::Enum)forceMode);
	}

	void ChocoGL_RigidBodyComponent_AddTorque(uint64_t entityID, glm::vec3* torque, ForceMode forceMode)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		physx::PxRigidActor* actor = (physx::PxRigidActor*)component.RuntimeActor;
		physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();

		// We don't want to assert since scripts might want to be able to switch
		// between a static and dynamic actor at runtime
		if (!dynamicActor)
			return;

		CL_CORE_ASSERT(torque);
		dynamicActor->addTorque({ torque->x, torque->y, torque->z }, (physx::PxForceMode::Enum)forceMode);
	}

	void ChocoGL_RigidBodyComponent_GetLinearVelocity(uint64_t entityID, glm::vec3* outVelocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		physx::PxRigidActor* actor = (physx::PxRigidActor*)component.RuntimeActor;
		physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();

		// We don't want to assert since scripts might want to be able to switch
		// between a static and dynamic actor at runtime
		if (!dynamicActor)
			return;

		CL_CORE_ASSERT(outVelocity);
		physx::PxVec3 velocity = dynamicActor->getLinearVelocity();
		*outVelocity = { velocity.x, velocity.y, velocity.z };
	}

	void ChocoGL_RigidBodyComponent_SetLinearVelocity(uint64_t entityID, glm::vec3* velocity)
	{
		Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
		CL_CORE_ASSERT(scene, "No active scene!");
		const auto& entityMap = scene->GetEntityMap();
		CL_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");

		Entity entity = entityMap.at(entityID);
		CL_CORE_ASSERT(entity.HasComponent<RigidBodyComponent>());
		auto& component = entity.GetComponent<RigidBodyComponent>();
		physx::PxRigidActor* actor = (physx::PxRigidActor*)component.RuntimeActor;
		physx::PxRigidDynamic* dynamicActor = actor->is<physx::PxRigidDynamic>();

		// We don't want to assert since scripts might want to be able to switch
		// between a static and dynamic actor at runtime
		if (!dynamicActor)
			return;

		CL_CORE_ASSERT(velocity);
		dynamicActor->setLinearVelocity({ velocity->x, velocity->y, velocity->z });
	}

	Ref<Mesh>* ChocoGL_Mesh_Constructor(MonoString* filepath)
	{
		return new Ref<Mesh>(new Mesh(mono_string_to_utf8(filepath)));
	}

	void ChocoGL_Mesh_Destructor(Ref<Mesh>* _this)
	{
		Ref<Mesh>* instance = (Ref<Mesh>*)_this;
		delete _this;
	}

	Ref<Material>* ChocoGL_Mesh_GetMaterial(Ref<Mesh>* inMesh)
	{
		Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
		return new Ref<Material>(mesh->GetMaterial());
	}

	Ref<MaterialInstance>* ChocoGL_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index)
	{
		Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
		const auto& materials = mesh->GetMaterials();
		
		CL_CORE_ASSERT(index < materials.size());
		return new Ref<MaterialInstance>(materials[index]);
	}

	int ChocoGL_Mesh_GetMaterialCount(Ref<Mesh>* inMesh)
	{
		Ref<Mesh>& mesh = *(Ref<Mesh>*)inMesh;
		const auto& materials = mesh->GetMaterials();
		return materials.size();
	}

	void* ChocoGL_Texture2D_Constructor(uint32_t width, uint32_t height)
	{
		auto result = Texture2D::Create(TextureFormat::RGBA, width, height);
		return new Ref<Texture2D>(result);
	}

	void ChocoGL_Texture2D_Destructor(Ref<Texture2D>* _this)
	{
		delete _this;
	}

	void ChocoGL_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count)
	{
		Ref<Texture2D>& instance = *_this;
		
		uint32_t dataSize = count * sizeof(glm::vec4) / 4;

		instance->Lock();
		Buffer buffer = instance->GetWriteableBuffer();
		CL_CORE_ASSERT(dataSize <= buffer.Size);
		// Convert RGBA32F color to RGBA8
		uint8_t* pixels = (uint8_t*)buffer.Data;
		uint32_t index = 0;
		for (int i = 0; i < instance->GetWidth() * instance->GetHeight(); i++)
		{
			glm::vec4& value = mono_array_get(inData, glm::vec4, i);
			*pixels++ = (uint32_t)(value.x * 255.0f);
			*pixels++ = (uint32_t)(value.y * 255.0f);
			*pixels++ = (uint32_t)(value.z * 255.0f);
			*pixels++ = (uint32_t)(value.w * 255.0f);
		}

		instance->Unlock();
	}

	void ChocoGL_Material_Destructor(Ref<Material>* _this)
	{
		delete _this;
	}

	void ChocoGL_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value)
	{
		Ref<Material>& instance = *(Ref<Material>*)_this;
		instance->Set(mono_string_to_utf8(uniform), value);
	}

	void ChocoGL_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture)
	{
		Ref<Material>& instance = *(Ref<Material>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *texture);
	}

	void ChocoGL_MaterialInstance_Destructor(Ref<MaterialInstance>* _this)
	{
		delete _this;
	}

	void ChocoGL_MaterialInstance_SetFloat(Ref<MaterialInstance>* _this, MonoString* uniform, float value)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), value);
	}

	void ChocoGL_MaterialInstance_SetVector3(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec3* value)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *value);
	}

	void ChocoGL_MaterialInstance_SetVector4(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec4* value)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *value);
	}

	void ChocoGL_MaterialInstance_SetTexture(Ref<MaterialInstance>* _this, MonoString* uniform, Ref<Texture2D>* texture)
	{
		Ref<MaterialInstance>& instance = *(Ref<MaterialInstance>*)_this;
		instance->Set(mono_string_to_utf8(uniform), *texture);
	}

	void* ChocoGL_MeshFactory_CreatePlane(float width, float height)
	{
		// TODO: Implement properly with MeshFactory class!
		return new Ref<Mesh>(new Mesh("assets/models/Plane1m.obj"));
	}

	////////////////////////////////////////////////////////////////

} }