#pragma once
#include "../../include/Appazoid/UI/Layer.h"
#include "imgui.h"

namespace az 
{
	class ImGuiLayer: Layer
	{
	public:
			void OnConstruction() override;
			void OnDestruction() override;
			virtual void OnEvent(Event& e) override;
			void Begin();
			void End();
			void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
	};

}