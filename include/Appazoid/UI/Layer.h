#pragma once
#include "imgui.h"
#include "Events/Event.h"


namespace az
{

	class Layer
	{
	protected:
		//ImGuiWindowFlags window_flags;
	public:
		bool visible = true;
		virtual ~Layer() = default;
		
		//On Rendering Widgets
		virtual void OnUIRender()		{}
		//On Rendering Frame
		virtual void OnBufferSwap()		{}

		virtual void OnEvent(Event&) {}
		virtual void OnConstruction()	{}
		virtual void OnDestruction()	{}
		/*virtual void SetFlags()
		{
			//To Disable Docking:
			//window_flags |= ImGuiWindowFlags_NoDocking; // or this: az::EnableWindowFlag(window_flags, ImGuiWindowFlags_NoDocking);
		}*/
		/*
		inline const ImGuiWindowFlags& GetFlags() const	{ return window_flags; }
		inline ImGuiWindowFlags& GetFlags()				{ return window_flags; }
		*/
	};

}