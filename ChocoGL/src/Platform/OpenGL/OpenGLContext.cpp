#include "clpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace ChocoGL {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CL_CORE_ASSERT(status, "Failed to initialize Glad!");

		
		CL_CORE_INFO("OpenGL Info:");
		CL_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		CL_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		CL_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
		
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}