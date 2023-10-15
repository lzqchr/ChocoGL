#include "clpch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRenderPass.h"


namespace ChocoGL {

	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:    CL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPIType::OpenGL:  return Ref<OpenGLRenderPass>::Create(spec);
		}

		CL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}