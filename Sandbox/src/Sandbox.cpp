#include <ChocoGL.h>
class ExampleLayer : public ChocoGL::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
		CL_INFO("ExampleLayer::Update");
	}
	void OnEvent(ChocoGL::Event& event) override
	{
		CL_TRACE("{0}", event);
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