#pragma once

#ifdef CL_PLATFORM_WINDOWS

extern ChocoGL::Application* ChocoGL::CreateApplication();

int main(int argc,char** argv)
{
	ChocoGL::Log::Init();
	CL_CORE_WARN("Initialized Log!");
	int a = 5;
	CL_INFO("Hello! Var={0}", a);

	auto app = ChocoGL::CreateApplication();
	app->Run();
	delete app;
}

#endif // CL_PLATFORM_WINDOWS
