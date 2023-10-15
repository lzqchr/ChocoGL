#include "clpch.h"
#include "ChocoGL\Core\Input.h"
#include "WindowsWindow.h"

#include "ChocoGL/Core/Application.h"

#include<GLFW/glfw3.h>

namespace ChocoGL {

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());

		auto state =glfwGetKey(window, static_cast<int32_t>(keycode));
		

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);


		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());

		double x, y;
		glfwGetCursorPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), &x, &y);
		return { (float)x, (float)y };

	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return (float)x;

	}
		
	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return (float)y;
	}

}