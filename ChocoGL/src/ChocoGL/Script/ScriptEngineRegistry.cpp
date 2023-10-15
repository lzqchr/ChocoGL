#include "clpch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ChocoGL/Scene/Entity.h"
#include "ScriptWrappers.h"
#include <iostream>

namespace ChocoGL {

	std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

	extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name("ChocoGL." #Type, s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			CL_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

	static void InitComponentTypes()
	{
		Component_RegisterType(TagComponent);
		Component_RegisterType(TransformComponent);
		Component_RegisterType(MeshComponent);
		Component_RegisterType(ScriptComponent);
		Component_RegisterType(CameraComponent);
		Component_RegisterType(SpriteRendererComponent);
	}

	void ScriptEngineRegistry::RegisterAll()
	{
		InitComponentTypes();

		mono_add_internal_call("ChocoGL.Noise::PerlinNoise_Native", ChocoGL::Script::ChocoGL_Noise_PerlinNoise);

		mono_add_internal_call("ChocoGL.Entity::GetTransform_Native", ChocoGL::Script::ChocoGL_Entity_GetTransform);
		mono_add_internal_call("ChocoGL.Entity::SetTransform_Native", ChocoGL::Script::ChocoGL_Entity_SetTransform);
		mono_add_internal_call("ChocoGL.Entity::CreateComponent_Native", ChocoGL::Script::ChocoGL_Entity_CreateComponent);
		mono_add_internal_call("ChocoGL.Entity::HasComponent_Native", ChocoGL::Script::ChocoGL_Entity_HasComponent);
		
		mono_add_internal_call("ChocoGL.MeshComponent::GetMesh_Native", ChocoGL::Script::ChocoGL_MeshComponent_GetMesh);
		mono_add_internal_call("ChocoGL.MeshComponent::SetMesh_Native", ChocoGL::Script::ChocoGL_MeshComponent_SetMesh);

		mono_add_internal_call("ChocoGL.Input::IsKeyPressed_Native", ChocoGL::Script::ChocoGL_Input_IsKeyPressed);

		mono_add_internal_call("ChocoGL.Texture2D::Constructor_Native", ChocoGL::Script::ChocoGL_Texture2D_Constructor);
		mono_add_internal_call("ChocoGL.Texture2D::Destructor_Native", ChocoGL::Script::ChocoGL_Texture2D_Destructor);
		mono_add_internal_call("ChocoGL.Texture2D::SetData_Native", ChocoGL::Script::ChocoGL_Texture2D_SetData);

		mono_add_internal_call("ChocoGL.Material::Destructor_Native", ChocoGL::Script::ChocoGL_Material_Destructor);
		mono_add_internal_call("ChocoGL.Material::SetFloat_Native", ChocoGL::Script::ChocoGL_Material_SetFloat);
		mono_add_internal_call("ChocoGL.Material::SetTexture_Native", ChocoGL::Script::ChocoGL_Material_SetTexture);

		mono_add_internal_call("ChocoGL.MaterialInstance::Destructor_Native", ChocoGL::Script::ChocoGL_MaterialInstance_Destructor);
		mono_add_internal_call("ChocoGL.MaterialInstance::SetFloat_Native", ChocoGL::Script::ChocoGL_MaterialInstance_SetFloat);
		mono_add_internal_call("ChocoGL.MaterialInstance::SetVector3_Native", ChocoGL::Script::ChocoGL_MaterialInstance_SetVector3);
		mono_add_internal_call("ChocoGL.MaterialInstance::SetTexture_Native", ChocoGL::Script::ChocoGL_MaterialInstance_SetTexture);

		mono_add_internal_call("ChocoGL.Mesh::Constructor_Native", ChocoGL::Script::ChocoGL_Mesh_Constructor);
		mono_add_internal_call("ChocoGL.Mesh::Destructor_Native", ChocoGL::Script::ChocoGL_Mesh_Destructor);
		mono_add_internal_call("ChocoGL.Mesh::GetMaterial_Native", ChocoGL::Script::ChocoGL_Mesh_GetMaterial);
		mono_add_internal_call("ChocoGL.Mesh::GetMaterialByIndex_Native", ChocoGL::Script::ChocoGL_Mesh_GetMaterialByIndex);
		mono_add_internal_call("ChocoGL.Mesh::GetMaterialCount_Native", ChocoGL::Script::ChocoGL_Mesh_GetMaterialCount);

		mono_add_internal_call("ChocoGL.MeshFactory::CreatePlane_Native", ChocoGL::Script::ChocoGL_MeshFactory_CreatePlane);

		// static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		// 
		// static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		// static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		// static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		// static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	}

}