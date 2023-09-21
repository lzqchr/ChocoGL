#include <ChocoGL.h>
#include <ChocoGL/EntryPoint.h>

#include "EditorLayer.h"

class CoCoApplication : public ChocoGL::Application
{
public:
	CoCoApplication(const ChocoGL::ApplicationProps& props)
		: Application(props)
	{
	}

	virtual void OnInit() override
	{
		PushLayer(new ChocoGL::EditorLayer());
	}
};

ChocoGL::Application* ChocoGL::CreateApplication()
{
	return new CoCoApplication({"CoCo", 1600, 900});
}