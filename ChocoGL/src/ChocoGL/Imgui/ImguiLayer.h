#pragma once 

#pragma once

#include "ChocoGL/Layer.h"


namespace ChocoGL {

	class ChocoGL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};

}