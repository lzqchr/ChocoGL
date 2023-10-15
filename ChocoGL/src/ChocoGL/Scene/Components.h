#pragma once
#include <glm/glm.hpp>

#include "ChocoGL/Renderer/Texture.h"
#include "ChocoGL/Renderer/Mesh.h"
#include "ChocoGL/Renderer/Camera.h"

namespace ChocoGL {

	struct TagComponent
	{
		std::string Tag;

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
	};

	struct TransformComponent
	{
		glm::mat4 Transform;

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct MeshComponent
	{
		Ref<ChocoGL::Mesh> Mesh;

		operator Ref<ChocoGL::Mesh>() { return Mesh; }
	};

	struct ScriptComponent
	{
		// TODO: C# script
		std::string ModuleName;
	};

	struct CameraComponent
	{
		//OrthographicCamera Camera;
		ChocoGL::Camera Camera;
		bool Primary = true;

		operator ChocoGL::Camera& () { return Camera; }
		operator const ChocoGL::Camera& () const { return Camera; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;
	};


}