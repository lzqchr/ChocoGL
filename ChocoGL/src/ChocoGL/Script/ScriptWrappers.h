#pragma once

#include "ChocoGL/Script/ScriptEngine.h"
#include "ChocoGL/Core/KeyCodes.h"

#include <glm/glm.hpp>

extern "C" {
	typedef struct _MonoString MonoString;
	typedef struct _MonoArray MonoArray;
}

namespace ChocoGL { namespace Script {

	// Math
	float ChocoGL_Noise_PerlinNoise(float x, float y);

	// Input
	bool ChocoGL_Input_IsKeyPressed(KeyCode key);

	// Entity
	void ChocoGL_Entity_GetTransform(uint32_t sceneID, uint32_t entityID, glm::mat4* outTransform);
	void ChocoGL_Entity_SetTransform(uint32_t sceneID, uint32_t entityID, glm::mat4* inTransform);
	void ChocoGL_Entity_CreateComponent(uint32_t sceneID, uint32_t entityID, void* type);
	bool ChocoGL_Entity_HasComponent(uint32_t sceneID, uint32_t entityID, void* type);

	void* ChocoGL_MeshComponent_GetMesh(uint32_t sceneID, uint32_t entityID);
	void ChocoGL_MeshComponent_SetMesh(uint32_t sceneID, uint32_t entityID, Ref<Mesh>* inMesh);

	// Renderer
	// Texture2D
	void* ChocoGL_Texture2D_Constructor(uint32_t width, uint32_t height);
	void ChocoGL_Texture2D_Destructor(Ref<Texture2D>* _this);
	void ChocoGL_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count);

	// Material
	void ChocoGL_Material_Destructor(Ref<Material>* _this);
	void ChocoGL_Material_SetFloat(Ref<Material>* _this, MonoString* uniform, float value);
	void ChocoGL_Material_SetTexture(Ref<Material>* _this, MonoString* uniform, Ref<Texture2D>* texture);

	void ChocoGL_MaterialInstance_Destructor(Ref<MaterialInstance>* _this);
	void ChocoGL_MaterialInstance_SetFloat(Ref<MaterialInstance>* _this, MonoString* uniform, float value);
	void ChocoGL_MaterialInstance_SetVector3(Ref<MaterialInstance>* _this, MonoString* uniform, glm::vec3* value);
	void ChocoGL_MaterialInstance_SetTexture(Ref<MaterialInstance>* _this, MonoString* uniform, Ref<Texture2D>* texture);

	// Mesh
	Ref<Mesh>* ChocoGL_Mesh_Constructor(MonoString* filepath);
	void ChocoGL_Mesh_Destructor(Ref<Mesh>* _this);
	Ref<Material>* ChocoGL_Mesh_GetMaterial(Ref<Mesh>* inMesh);
	Ref<MaterialInstance>* ChocoGL_Mesh_GetMaterialByIndex(Ref<Mesh>* inMesh, int index);
	int ChocoGL_Mesh_GetMaterialCount(Ref<Mesh>* inMesh);

	void* ChocoGL_MeshFactory_CreatePlane(float width, float height);
} }