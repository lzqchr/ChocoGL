#pragma once

#include"ChocoGL/Core.h"

namespace ChocoGL {

	class ChocoGL_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instancel->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instancel->IsMouseButtonPressedImpl(button); }

		inline static float GetMouseX( ) { return s_Instancel->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instancel->GetMouseYImpl(); }

		inline static std::pair<float,float>GetMousePosition() { return s_Instancel->GetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instancel;
	};

}