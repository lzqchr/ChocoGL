#pragma once 

#include "ChocoGL/Core/Layer.h"

#include "ChocoGL/Core/Events/ApplicationEvent.h"
#include "ChocoGL/Core/Events/KeyEvent.h"
#include "ChocoGL/Core/Events/MouseEvent.h"

namespace ChocoGL {

	class ChocoGL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		~ImGuiLayer();

		void Begin();
		void End();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		

		
	private:
		float m_Time = 0.0f;
	};

}