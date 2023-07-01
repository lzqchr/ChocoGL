#pragma once

#include "Core.h"

namespace ChocoGL {
	class ChocoGL_API Application
	{
	public:
		Application();
		virtual~Application();
		void Run();

	};
	Application* CreatApplication();
}
