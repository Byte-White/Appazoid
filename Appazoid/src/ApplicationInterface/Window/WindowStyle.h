#pragma once

#include "glm/glm.hpp"
#include <string>
namespace az
{


enum class StyleColor
{
	CustomStyleColors = 0, StyleColorDark, StyleColorLight, StyleColorClassic
};


struct WindowStyle
{
private:
	//Copy
	void Copy(const WindowStyle& ws)
	{
		this->stylecolor = ws.stylecolor;
		this->colors = ws.colors;
		this->FontGlobalScale = ws.FontGlobalScale;
		this->size = ws.size;
		this->title = ws.title;
		this->monitor = ws.monitor;
	}
public:
	WindowStyle(int w, int h, std::string window_title = "Appazoid Application")
		:width(w), height(h), title(window_title)
	{}

	WindowStyle(glm::ivec2 sz, std::string window_title = "Appazoid Application")
		:size(sz), title(window_title)
	{}

	WindowStyle()
	{}

	WindowStyle(const WindowStyle& ws)
	{
		Copy(ws);
	}

	void operator=(const WindowStyle& ws)
	{
		Copy(ws);
	}

	union
	{
		struct
		{
			int width, height;
		};
		glm::ivec2 size;
	};
	std::string title;
	StyleColor stylecolor = StyleColor::CustomStyleColors;

	//bool fullscreen = false;  //not needed
	GLFWmonitor* monitor = NULL;//Used to select monitor for fullscreen

	struct
	{
		glm::vec3 Text = glm::vec3{ 1,1,1 };
		glm::vec3 TextDisabled = glm::vec3{ 0.5,0.5,0.5 };
		glm::vec3 WindowBg = glm::vec3{ 0.06,0.06,0.06 };
		glm::vec3 ChildBg = glm::vec3{ 0,0,0 };
		glm::vec3 PopupBg = glm::vec3{ 0.08,0.08,0.08 };
		glm::vec3 Border = glm::vec3{ 0.43,0.43,0.43 };
		glm::vec3 BorderShadow = glm::vec3{ 0,0,0 };
		glm::vec3 FrameBg = glm::vec3{ 0.16,0.16,0.16 };
		glm::vec3 FrameBgHovered = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 FrameBgActive = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 TitleBg = glm::vec3{ 0.04,0.04,0.04 };
		glm::vec3 TitleBgActive = glm::vec3{ 0.16,0.16,0.16 };
		glm::vec3 TitleBgCollapsed = glm::vec3{ 0,0,0 };
		glm::vec3 MenuBarBg = glm::vec3{ 0.14,0.14,0.14 };
		glm::vec3 ScrollbarBg = glm::vec3{ 0.02,0.02,0.02 };
		glm::vec3 ScrollbarGrab = glm::vec3{ 0.31,0.31,0.31 };
		glm::vec3 ScrollbarGrabHovered = glm::vec3{ 0.41,0.41,0.41 };
		glm::vec3 ScrollbarGrabActive = glm::vec3{ 0.51,0.51,0.51 };
		glm::vec3 CheckMark = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 SliderGrab = glm::vec3{ 0.24,0.24,0.24 };
		glm::vec3 SliderGrabActive = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 Button = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 ButtonHovered = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 ButtonActive = glm::vec3{ 0.06,0.06,0.06 };
		glm::vec3 Header = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 HeaderHovered = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 HeaderActive = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 Separator = glm::vec3{ 0.43,0.43,0.43 };
		glm::vec3 SeparatorHovered = glm::vec3{ 0.1,0.1,0.1 };
		glm::vec3 SeparatorActive = glm::vec3{ 0.1,0.1,0.1 };
		glm::vec3 ResizeGrip = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 ResizeGripHovered = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 ResizeGripActive = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 Tab = glm::vec3{ 0.18,0.18,0.18 };
		glm::vec3 TabHovered = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 TabActive = glm::vec3{ 0.2,0.2,0.2 };
		glm::vec3 TabUnfocused = glm::vec3{ 0.068,0.068,0.068 };
		glm::vec3 TabUnfocusedActive = glm::vec3{ 0.136,0.136,0.136 };
		glm::vec3 DockingPreview = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 DockingEmptyBg = glm::vec3{ 0.2,0.2,0.2 };
		glm::vec3 PlotLines = glm::vec3{ 0.61,0.61,0.61 };
		glm::vec3 PlotLinesHovered = glm::vec3{ 1,1,1 };
		glm::vec3 PlotHistogram = glm::vec3{ 0.9,0.9,0.9 };
		glm::vec3 PlotHistogramHovered = glm::vec3{ 1,1,1 };
		glm::vec3 TableHeaderBg = glm::vec3{ 0.19,0.19,0.19 };
		glm::vec3 TableBorderStrong = glm::vec3{ 0.31,0.31,0.31 };
		glm::vec3 TableBorderLight = glm::vec3{ 0.23,0.23,0.23 };
		glm::vec3 TableRowBg = glm::vec3{ 0,0,0 };
		glm::vec3 TableRowBgAlt = glm::vec3{ 1,1,1 };
		glm::vec3 TextSelectedBg = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 DragDropTarget = glm::vec3{ 1,1,1 };
		glm::vec3 NavHighlight = glm::vec3{ 0.26,0.26,0.26 };
		glm::vec3 NavWindowingHighlight = glm::vec3{ 1,1,1 };
		glm::vec3 NavWindowingDimBg = glm::vec3{ 0.8,0.8,0.8 };
		glm::vec3 ModalWindowDimBg = glm::vec3{ 0.8,0.8,0.8 };
	}colors;
	float FontGlobalScale = 1.f;
};

}