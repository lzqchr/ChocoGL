#include "clpch.h"
#include "RenderCommandQueue.h"

#define CL_RENDER_TRACE(...) CL_CORE_TRACE(__VA_ARGS__)

namespace ChocoGL {

	RenderCommandQueue::RenderCommandQueue()
	{
		m_CommandBuffer = new unsigned char[10 * 1024 * 1024]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{

		delete[] m_CommandBuffer;

	}




	void* RenderCommandQueue::Allocate(RenderCommandFn fn, unsigned int size)

	{
		//m_CommandBufferPtr  
		// &fn sizeof(fn) &fn1 sizeof(fn1) &fn2 sizeof(fn2)
		// TODO: alignment

		*(RenderCommandFn*)m_CommandBufferPtr = fn;

		m_CommandBufferPtr += sizeof(RenderCommandFn);




		*(int*)m_CommandBufferPtr = size;

		m_CommandBufferPtr += sizeof(unsigned int);


		void* memory = m_CommandBufferPtr;

		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}




	void RenderCommandQueue::Execute()

	{

	//	CL_RENDER_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));


		byte* buffer = m_CommandBuffer;


		for (unsigned int i = 0; i < m_CommandCount; i++)

		{

			RenderCommandFn function = *(RenderCommandFn*)buffer;

			buffer += sizeof(RenderCommandFn);





			unsigned int size = *(unsigned int*)buffer;

			buffer += sizeof(unsigned int);

			function(buffer);

			buffer += size;

		}

		m_CommandBufferPtr = m_CommandBuffer;

		m_CommandCount = 0;

	}

}