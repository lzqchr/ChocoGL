#include "clpch.h"
#include "ChocoGL\Core\Input.h"
#include "WindowsWindow.h"

#include "ChocoGL/Core/Application.h"

#include<GLFW/glfw3.h>

namespace ChocoGL {

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());

		auto state =glfwGetKey(window, keycode);
		

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);


		return state == GLFW_PRESS;
	}

	/*std::pair<float, float> WinodwsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos,(float)ypos };

	}*/

	float Input::GetMouseX()
	{
		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());
		double xpos, ypos;
		glfwGetCursorPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), &xpos, &ypos);
		return (float)xpos;

	}
		
	float Input::GetMouseY()
	{
		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());
		double xpos, ypos;
		glfwGetCursorPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), &xpos, &ypos);
		return (float)ypos;
	}

}