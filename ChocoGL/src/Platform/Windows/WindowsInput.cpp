#include"clpch.h"
#include"WindowsInput.h"

#include<GLFW/glfw3.h>
#include"ChocoGL/Application.h"

namespace ChocoGL {

	Input* Input::s_Instancel = new WinodwsInput();

	bool WinodwsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());

		auto state =glfwGetKey(window, keycode);
		

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WinodwsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);


		return state == GLFW_PRESS;
	}

	std::pair<float, float> WinodwsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);


		return { (float)xpos,(float)ypos };
	}

	float WinodwsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return x;
	}
	float WinodwsInput::GetMouseYImpl()
	{
		/*
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		*/

		auto [x, y] = GetMousePositionImpl();

		return y;
	}

}