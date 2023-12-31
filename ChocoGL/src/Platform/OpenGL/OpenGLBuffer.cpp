#include "clpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include "ChocoGL/Renderer/Renderer.h"
namespace ChocoGL {

	//////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer
	//////////////////////////////////////////////////////////////////////////////////

	static GLenum OpenGLUsage(VertexBufferUsage usage)
	{
		switch (usage)
		{
		case VertexBufferUsage::Static:    return GL_STATIC_DRAW;
		case VertexBufferUsage::Dynamic:   return GL_DYNAMIC_DRAW;
		}
		CL_CORE_ASSERT(false, "Unknown vertex buffer usage");
		return 0;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, uint32_t size, VertexBufferUsage usage)
		: m_Size(size), m_Usage(usage)
	{
		m_LocalData = Buffer::Copy(data, size);

		Ref<OpenGLVertexBuffer> instance = this;
		Renderer::Submit([instance]() mutable
			{
				glCreateBuffers(1, &instance->m_RendererID);
				glNamedBufferData(instance->m_RendererID, instance->m_Size, instance->m_LocalData.Data, OpenGLUsage(instance->m_Usage));
			});
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, VertexBufferUsage usage)
		: m_Size(size), m_Usage(usage)
	{
		Ref<OpenGLVertexBuffer> instance = this;
		Renderer::Submit([instance]() mutable
			{
				glCreateBuffers(1, &instance->m_RendererID);
				glNamedBufferData(instance->m_RendererID, instance->m_Size, nullptr, OpenGLUsage(instance->m_Usage));
			});
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GLuint rendererID = m_RendererID;
		Renderer::Submit([rendererID]() {
			glDeleteBuffers(1, &rendererID);
			});
	}

	void OpenGLVertexBuffer::SetData(void* data, uint32_t size, uint32_t offset)
	{
		m_LocalData = Buffer::Copy(data, size);
		m_Size = size;
		Ref<OpenGLVertexBuffer> instance = this;
		Renderer::Submit([instance, offset]() {
			glNamedBufferSubData(instance->m_RendererID, offset, instance->m_Size, instance->m_LocalData.Data);
			});
	}

	void OpenGLVertexBuffer::Bind() const
	{
		Ref<const OpenGLVertexBuffer> instance = this;
		Renderer::Submit([instance]() {
			glBindBuffer(GL_ARRAY_BUFFER, instance->m_RendererID);
			});
	}

	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, uint32_t size)
		: m_RendererID(0), m_Size(size)
	{
		m_LocalData = Buffer::Copy(data, size);

		Ref<OpenGLIndexBuffer> instance = this;
		Renderer::Submit([instance]() mutable {
			glCreateBuffers(1, &instance->m_RendererID);
			glNamedBufferData(instance->m_RendererID, instance->m_Size, instance->m_LocalData.Data, GL_STATIC_DRAW);
		});
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t size)
		:	m_Size(size)
	{
		// m_LocalData = Buffer(size);

		Ref<OpenGLIndexBuffer> instance = this;
		Renderer::Submit([instance]() mutable {
			glCreateBuffers(1, &instance->m_RendererID);
			glNamedBufferData(instance->m_RendererID, instance->m_Size, nullptr, GL_DYNAMIC_DRAW);
			});
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GLuint rendererID = m_RendererID;
		Renderer::Submit([rendererID]() {
			glDeleteBuffers(1, &rendererID);
			});
	}

	void OpenGLIndexBuffer::SetData(void* data, uint32_t size, uint32_t offset)
	{
		m_LocalData = Buffer::Copy(data, size);
		m_Size = size;
		Ref<OpenGLIndexBuffer> instance = this;
		Renderer::Submit([instance, offset]() {
			glNamedBufferSubData(instance->m_RendererID, offset, instance->m_Size, instance->m_LocalData.Data);
			});
	}

	void OpenGLIndexBuffer::Bind() const
	{
		Ref<const OpenGLIndexBuffer> instance = this;
		Renderer::Submit([instance]() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instance->m_RendererID);
			});
	}

}