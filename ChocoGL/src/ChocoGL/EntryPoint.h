#pragma once

#ifdef CL_PLATFORM_WINDOWS

extern ChocoGL::Application* ChocoGL::CreatApplication();

int main(int argc,char** argv)
{
	ChocoGL::Log::Init();
	ChocoGL::Log::GetCoreLogger()->warn("no log!!!!!!!!");
	ChocoGL::Log::GetClientLogger()->info("no log!!!!!!!!");

	auto app = ChocoGL::CreatApplication();

	app->Run();

	delete app;
}

#endif // CL_PLATFORM_WINDOWS
