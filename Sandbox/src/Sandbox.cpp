#include <ChocoGL.h>

#include "imgui/imgui.h"

class ExampleLayer : public ChocoGL::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
		//CL_INFO("ExampleLayer::Update");

		if (ChocoGL::Input::IsKeyPressed(CL_KEY_TAB))
			CL_TRACE("Tab key is pressed (poll)!");
	}
	void OnEvent(ChocoGL::Event& event) override
	{
		//CL_TRACE("{0}", event);

		if (event.GetEventType() == ChocoGL::EventType::KeyPressed)
		{
			ChocoGL::KeyPressedEvent& e = (ChocoGL::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CL_KEY_TAB)
				CL_TRACE("Tab key is pressed (event)!");
			CL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};
class Sandbox : public ChocoGL::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ChocoGL::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};
ChocoGL::Application* ChocoGL::CreateApplication()
{
	return new Sandbox();
}