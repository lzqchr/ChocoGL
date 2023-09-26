#include "clpch.h"
#include "Renderer.h"

#include "Shader.h"
#include "Mesh.h"

#include <glad/glad.h>

namespace ChocoGL {

	Renderer* Renderer::s_Instance = new Renderer();
	RendererAPIType RendererAPI::s_CurrentRendererAPI = RendererAPIType::OpenGL;

	void Renderer::Init()
	{
		s_Instance->m_ShaderLibrary = std::make_unique<ShaderLibrary>();
		Renderer::Submit([]() { RendererAPI::Init(); });

		Renderer::GetShaderLibrary()->Load("assets/shaders/ChocoGLPBR_Static.glsl");
		Renderer::GetShaderLibrary()->Load("assets/shaders/ChocoGLPBR_Anim.glsl");
	}



	void Renderer::Clear()
	{
		Renderer::Submit([]() {
			RendererAPI::Clear(0.0f, 0.0f, 0.0f, 1.0f);
			});
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		Renderer::Submit([=]() {
			RendererAPI::Clear(r, g, b, a);
			});
	}

	void Renderer::ClearMagenta()
	{
		Clear(1, 0, 1);
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
	}

	void Renderer::DrawIndexed(uint32_t count, bool depthTest)
	{
		Renderer::Submit([=]() {
			RendererAPI::DrawIndexed(count, depthTest);
			});
	}

	void Renderer::WaitAndRender()
	{
		s_Instance->m_CommandQueue.Execute();
	}
	void Renderer::IBeginRenderPass(const Ref<RenderPass>& renderPass)
	{
		// TODO: Convert all of this into a render command buffer
		m_ActiveRenderPass = renderPass;

		renderPass->GetSpecification().TargetFramebuffer->Bind();
		const glm::vec4& clearColor = renderPass->GetSpecification().TargetFramebuffer->GetSpecification().ClearColor;
		Renderer::Submit([=]() {
			RendererAPI::Clear(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
			});
	}

	void Renderer::IEndRenderPass()
	{
		CL_CORE_ASSERT(m_ActiveRenderPass, "No active render pass! Have you called Renderer::EndRenderPass twice?");
		m_ActiveRenderPass->GetSpecification().TargetFramebuffer->Unbind();
		m_ActiveRenderPass = nullptr;
	}

	void Renderer::SubmitMeshI(const Ref<Mesh>& mesh, const glm::mat4& transform, const Ref<MaterialInstance>& overrideMaterial)
	{
		if (overrideMaterial)
		{
			overrideMaterial->Bind();
		}
		else
		{
			// Bind mesh material here
		}

		// TODO: Sort this out
		mesh->m_VertexArray->Bind();

		// TODO: replace with render API calls
		Renderer::Submit([=]()
			{
				for (Submesh& submesh : mesh->m_Submeshes)
				{
					if (mesh->m_IsAnimated)
					{
						for (size_t i = 0; i < mesh->m_BoneTransforms.size(); i++)
						{
							std::string uniformName = std::string("u_BoneTransforms[") + std::to_string(i) + std::string("]");
							mesh->m_MeshShader->SetMat4FromRenderThread(uniformName, mesh->m_BoneTransforms[i]);
						}
					}

					glDrawElementsBaseVertex(GL_TRIANGLES, submesh.IndexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * submesh.BaseIndex), submesh.BaseVertex);
				}
			});
	}
}