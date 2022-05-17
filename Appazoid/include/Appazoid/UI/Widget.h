#pragma once

#include "imgui.h"

namespace az
{

	class Widget
	{
	protected:
		//ImGuiWindowFlags window_flags;
	public:
		bool visible = true;
		virtual ~Widget() = default;
		
		//On Rendering Widgets
		virtual void OnRender(){}
		//On Rendering ImGui Frame
		virtual void OnImGuiRender(){}
		
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