#pragma once

#include "Core.h"

#include "Window.h"
#include "ChocoGL/LayerStack.h"
#include "ChocoGL/Events/Event.h"
#include "ChocoGL/Events/ApplicationEvent.h"


namespace ChocoGL {
	class ChocoGL_API Application
	{
	public:
		Application();
		virtual~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};
	Application* CreatApplication();
}
