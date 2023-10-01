#pragma once

#include "ChocoGL/Core/Core.h"
#include "ChocoGL/Core/Events/Event.h"
#include "ChocoGL/Core/Timestep.h"

namespace ChocoGL {

	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}