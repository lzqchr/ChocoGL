#include "clpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include"Platform/OpenGL/OpenGLIndexBuffer.h"

namespace ChocoGL {

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:    return nullptr;
		case RendererAPIType::OpenGL:  return Ref<OpenGLIndexBuffer>::Create(size);
		}
		CL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:    return nullptr;
		case RendererAPIType::OpenGL:  return Ref<OpenGLIndexBuffer>::Create(data, size);
		}
		CL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}