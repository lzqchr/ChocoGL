#include "clpch.h"
#include "Application.h"

#include"ChocoGL/Log.h"

#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

namespace ChocoGL {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));


		CL_CORE_INFO("{0}", e);

	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;

		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}