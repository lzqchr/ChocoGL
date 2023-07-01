#pragma once

#ifdef CL_PLATFORM_WINDOWS

extern ChocoGL::Application* ChocoGL::CreatApplication();

int main(int argc,char** argv)
{
	auto app = ChocoGL::CreatApplication();

	app->Run();

	delete app;
}

#endif // CL_PLATFORM_WINDOWS
