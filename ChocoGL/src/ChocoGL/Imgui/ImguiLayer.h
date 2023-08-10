#pragma once 

#include "ChocoGL/Layer.h"

#include "ChocoGL/Events/ApplicationEvent.h"
#include "ChocoGL/Events/KeyEvent.h"
#include "ChocoGL/Events/MouseEvent.h"

namespace ChocoGL {

	class ChocoGL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};

}