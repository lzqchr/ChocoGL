#pragma once

#include "ChocoGL/Scene/Scene.h"
#include "ChocoGL/Scene/Entity.h"
#include "ChocoGL/Renderer/Mesh.h"

namespace ChocoGL {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);
		void SetSelected(Entity entity);
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawMeshNode(const Ref<Mesh>& mesh, uint32_t& imguiMeshID);
		void MeshNodeHierarchy(const Ref<Mesh>& mesh, aiNode* node, const glm::mat4& parentTransform = glm::mat4(1.0f), uint32_t level = 0);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}