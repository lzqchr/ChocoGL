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

		CL_RENDER_S({
			glCreateBuffers(1, &self->m_RendererID);
			glNamedBufferData(self->m_RendererID, self->m_Size, self->m_LocalData.Data, OpenGLUsage(self->m_Usage));
			});
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, VertexBufferUsage usage)
		: m_Size(size), m_Usage(usage)
	{
		CL_RENDER_S({
			glCreateBuffers(1, &self->m_RendererID);
			glNamedBufferData(self->m_RendererID, self->m_Size, nullptr, OpenGLUsage(self->m_Usage));
			});
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		CL_RENDER_S({
			glDeleteBuffers(1, &self->m_RendererID);
			});
	}

	void OpenGLVertexBuffer::SetData(void* data, uint32_t size, uint32_t offset)
	{
		m_LocalData = Buffer::Copy(data, size);
		m_Size = size;
		CL_RENDER_S1(offset, {
			glNamedBufferSubData(self->m_RendererID, offset, self->m_Size, self->m_LocalData.Data);
			});
	}

	void OpenGLVertexBuffer::Bind() const
	{
		CL_RENDER_S({
			glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			});
	}

	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, uint32_t size)
		: m_RendererID(0), m_Size(size)
	{
		m_LocalData = Buffer::Copy(data, size);

		CL_RENDER_S({
			glCreateBuffers(1, &self->m_RendererID);
			glNamedBufferData(self->m_RendererID, self->m_Size, self->m_LocalData.Data, GL_STATIC_DRAW);
			});
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		CL_RENDER_S({
			glDeleteBuffers(1, &self->m_RendererID);
			});
	}

	void OpenGLIndexBuffer::SetData(void* data, uint32_t size, uint32_t offset)
	{
		m_LocalData = Buffer::Copy(data, size);
		m_Size = size;
		CL_RENDER_S1(offset, {
			glNamedBufferSubData(self->m_RendererID, offset, self->m_Size, self->m_LocalData.Data);
			});
	}

	void OpenGLIndexBuffer::Bind() const
	{
		CL_RENDER_S({
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			});
	}

}