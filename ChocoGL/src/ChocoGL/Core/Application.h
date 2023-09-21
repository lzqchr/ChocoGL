#pragma once

#include "Core.h"

#include "Window.h"
#include "ChocoGL/Core/LayerStack.h"
#include "ChocoGL/Core/Events/Event.h"
#include "ChocoGL/Core/Events/ApplicationEvent.h"

#include "ChocoGL/ImGui/ImGuiLayer.h"

#include "ChocoGL/Renderer/Shader.h"
#include "ChocoGL/Renderer/Buffer.h"

#include"ChocoGL\Core/TimeStep.h"

/*
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


		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};
	Application* CreateApplication();
}
*/

namespace ChocoGL {

	struct ApplicationProps
	{
		std::string Name;
		uint32_t WindowWidth, WindowHeight;
	};

	class  Application
	{
	public:
		Application(const ApplicationProps& props = { "ChocoGL Engine", 1280, 720 });;
		virtual ~Application();

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate(TimeStep ts) {}

		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void RenderImGui();

		std::string OpenFile(const std::string& filter) const;

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }

		float GetTime() const; // TODO: This should be in "Platform"
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		TimeStep m_TimeStep;

		float m_LastFrameTime = 0.0f;


		static Application* s_Instance;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}