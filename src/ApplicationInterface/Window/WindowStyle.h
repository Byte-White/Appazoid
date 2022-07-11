#pragma once

#include "glm/glm.hpp"
#include <imgui.h>
#include "Core/Input.h"
#include <string>
#include <sstream>
#include "Events/Event.h"
namespace az
{


enum class StyleColor
{
	/*CustomStyleColors = 0,*/ StyleColorDark=0, StyleColorLight, StyleColorClassic
};


struct WindowStyle
{

	//EventCallbackFn EventCallback;
private:
	//Copy
	void Copy(const WindowStyle& ws)
	{
		this->stylecolor = ws.stylecolor;
		//this->colors = ws.colors;
		this->FontGlobalScale = ws.FontGlobalScale;
		this->size = ws.size;
		this->title = ws.title;
		this->monitor = ws.monitor;
	}
public:
	EventCallbackFn EventCallback;
	bool VSync;


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


	//Generates the name of the color edit
	#define AZ_COLOR_EDIT_TOSTR_HELPER_FUNC(x,y) x##y
	//Generates the coloredit widget
	#define AZ_COLOR_EDIT_HELPER_FUNC(name)\
	ImGui::ColorEdit4(AZ_COLOR_EDIT_TOSTR_HELPER_FUNC("colors.",#name), &colors.##name->x)

	#define AZ_GENERATE_CLR_CODE_HELPER_FUNC(name)\
	colors.name = 
	std::string GenerateCustomColorsCode()
	{
		auto vec4_to_str = [](WindowColors::color_vec_ref clr) {
			std::stringstream ss;
			ss << "ImVec4{";
			ss << clr->x;
			ss << ",";
			ss << clr->y;
			ss << ",";
			ss << clr->z;
			ss << "}";
			
			return ss.str();
		};
			
			
		std::string result;
		for (int i = 0; i < colors.get_count(); i++)
		{

			std::string line = "";
			line += "colors.";
			line += WindowColors::get_name_by_id(i);
			int line_length = line.length();
			for (int j = 0; j < 40-line_length; j++) line+=" ";
			line += "= ";
			line += vec4_to_str(colors.get_color_ref_by_id(i));
			line += ";\n";
			result += line;
		}
		result += "FontGlobalScale = ";
		result += std::to_string(FontGlobalScale);
		result += ";";
		return result;
	}

	void ColorEditor()
	{
		AZ_COLOR_EDIT_HELPER_FUNC(Text);
		AZ_COLOR_EDIT_HELPER_FUNC(TextDisabled);
		AZ_COLOR_EDIT_HELPER_FUNC(WindowBg);
		AZ_COLOR_EDIT_HELPER_FUNC(ChildBg);
		AZ_COLOR_EDIT_HELPER_FUNC(PopupBg);
		AZ_COLOR_EDIT_HELPER_FUNC(Border);
		AZ_COLOR_EDIT_HELPER_FUNC(BorderShadow);
		AZ_COLOR_EDIT_HELPER_FUNC(FrameBg);
		AZ_COLOR_EDIT_HELPER_FUNC(FrameBgHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(FrameBgActive);
		AZ_COLOR_EDIT_HELPER_FUNC(TitleBg);
		AZ_COLOR_EDIT_HELPER_FUNC(TitleBgActive);
		AZ_COLOR_EDIT_HELPER_FUNC(TitleBgCollapsed);
		AZ_COLOR_EDIT_HELPER_FUNC(MenuBarBg);
		AZ_COLOR_EDIT_HELPER_FUNC(ScrollbarBg);
		AZ_COLOR_EDIT_HELPER_FUNC(ScrollbarGrab);
		AZ_COLOR_EDIT_HELPER_FUNC(ScrollbarGrabHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(ScrollbarGrabActive);
		AZ_COLOR_EDIT_HELPER_FUNC(CheckMark);
		AZ_COLOR_EDIT_HELPER_FUNC(SliderGrab);
		AZ_COLOR_EDIT_HELPER_FUNC(SliderGrabActive);
		AZ_COLOR_EDIT_HELPER_FUNC(Button);
		AZ_COLOR_EDIT_HELPER_FUNC(ButtonHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(ButtonActive);
		AZ_COLOR_EDIT_HELPER_FUNC(Header);
		AZ_COLOR_EDIT_HELPER_FUNC(HeaderHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(HeaderActive);
		AZ_COLOR_EDIT_HELPER_FUNC(Separator);
		AZ_COLOR_EDIT_HELPER_FUNC(SeparatorHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(SeparatorActive);
		AZ_COLOR_EDIT_HELPER_FUNC(ResizeGrip);
		AZ_COLOR_EDIT_HELPER_FUNC(ResizeGripHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(ResizeGripActive);
		AZ_COLOR_EDIT_HELPER_FUNC(Tab);
		AZ_COLOR_EDIT_HELPER_FUNC(TabHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(TabActive);
		AZ_COLOR_EDIT_HELPER_FUNC(TabUnfocused);
		AZ_COLOR_EDIT_HELPER_FUNC(TabUnfocusedActive);
		AZ_COLOR_EDIT_HELPER_FUNC(DockingPreview);
		AZ_COLOR_EDIT_HELPER_FUNC(DockingEmptyBg);
		AZ_COLOR_EDIT_HELPER_FUNC(PlotLines);
		AZ_COLOR_EDIT_HELPER_FUNC(PlotLinesHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(PlotHistogram);
		AZ_COLOR_EDIT_HELPER_FUNC(PlotHistogramHovered);
		AZ_COLOR_EDIT_HELPER_FUNC(TableHeaderBg);
		AZ_COLOR_EDIT_HELPER_FUNC(TableBorderStrong);
		AZ_COLOR_EDIT_HELPER_FUNC(TableBorderLight);
		AZ_COLOR_EDIT_HELPER_FUNC(TableRowBg);
		AZ_COLOR_EDIT_HELPER_FUNC(TableRowBgAlt);
		AZ_COLOR_EDIT_HELPER_FUNC(TextSelectedBg);
		AZ_COLOR_EDIT_HELPER_FUNC(DragDropTarget);
		AZ_COLOR_EDIT_HELPER_FUNC(NavHighlight);
		AZ_COLOR_EDIT_HELPER_FUNC(NavWindowingHighlight);
		AZ_COLOR_EDIT_HELPER_FUNC(NavWindowingDimBg);
		AZ_COLOR_EDIT_HELPER_FUNC(ModalWindowDimBg);
		static float min=0.1f;
		static float max=2.0f;
		static float speed = 0.001f;
		ImGui::DragFloat("FontGlobalScale", &FontGlobalScale,speed,min,max);
		FontGlobalScale = std::max(min,std::min(max,FontGlobalScale));//clamping the value between min and max
		
		static bool show_successful_code_generation_window = false;
		std::string code = GenerateCustomColorsCode();
		if (ImGui::Button("Generate Code"))		
			show_successful_code_generation_window = true;

		if(show_successful_code_generation_window)
		{
			//ImGui::SetNextWindowSize(ImVec2(400,100));
			ImGui::Begin("Code Generated Successfully",&show_successful_code_generation_window,ImGuiWindowFlags_NoDocking 
				/* | ImGuiWindowFlags_NoSavedSettings*/);
			ImGui::Text(code.c_str());
			if(ImGui::Button("Copy To Clipboard"))
				glfwSetClipboardString(*Input::GetWindow(), code.c_str());
			ImGui::SameLine();
			if(ImGui::Button("Close"))show_successful_code_generation_window = false;
			ImGui::End();
		}
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
	StyleColor stylecolor = StyleColor::StyleColorDark;

	//bool fullscreen = false;  //not needed
	GLFWmonitor* monitor = NULL;//Used to select monitor for fullscreen



	struct WindowColors
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
	public:
		using color_vec = ImVec4;
		using color_vec_ref = color_vec*;

		static std::string names[55];
		static std::string& get_name_by_id(unsigned int id)
		{
			return names[id];
		}
		color_vec_ref get_color_ref_by_id(unsigned int id)
		{
			return *(&Text + id);
		}

		const int get_count()
		{
			return 55;// (&ModalWindowDimBg - &Text) / sizeof(color_vec_ref);
		}
		color_vec_ref Text					= &colors[ImGuiCol_Text];
		color_vec_ref TextDisabled			= &colors[ImGuiCol_TextDisabled];
		color_vec_ref WindowBg				= &colors[ImGuiCol_WindowBg];
		color_vec_ref ChildBg				= &colors[ImGuiCol_ChildBg];
		color_vec_ref PopupBg				= &colors[ImGuiCol_PopupBg];
		color_vec_ref Border				= &colors[ImGuiCol_Border];
		color_vec_ref BorderShadow			= &colors[ImGuiCol_BorderShadow];
		color_vec_ref FrameBg				= &colors[ImGuiCol_FrameBg];
		color_vec_ref FrameBgHovered		= &colors[ImGuiCol_FrameBgHovered];
		color_vec_ref FrameBgActive			= &colors[ImGuiCol_FrameBgActive];
		color_vec_ref TitleBg				= &colors[ImGuiCol_TitleBg];
		color_vec_ref TitleBgActive			= &colors[ImGuiCol_TitleBgActive];
		color_vec_ref TitleBgCollapsed		= &colors[ImGuiCol_TitleBgCollapsed];
		color_vec_ref MenuBarBg				= &colors[ImGuiCol_MenuBarBg];
		color_vec_ref ScrollbarBg			= &colors[ImGuiCol_ScrollbarBg];
		color_vec_ref ScrollbarGrab			= &colors[ImGuiCol_ScrollbarGrab];
		color_vec_ref ScrollbarGrabHovered	= &colors[ImGuiCol_ScrollbarGrabHovered];
		color_vec_ref ScrollbarGrabActive	= &colors[ImGuiCol_ScrollbarGrabActive];
		color_vec_ref CheckMark				= &colors[ImGuiCol_CheckMark];
		color_vec_ref SliderGrab			= &colors[ImGuiCol_SliderGrab];
		color_vec_ref SliderGrabActive		= &colors[ImGuiCol_SliderGrabActive];
		color_vec_ref Button				= &colors[ImGuiCol_Button];
		color_vec_ref ButtonHovered			= &colors[ImGuiCol_ButtonHovered];
		color_vec_ref ButtonActive			= &colors[ImGuiCol_ButtonActive];
		color_vec_ref Header				= &colors[ImGuiCol_Header];
		color_vec_ref HeaderHovered			= &colors[ImGuiCol_HeaderHovered];
		color_vec_ref HeaderActive			= &colors[ImGuiCol_HeaderActive];
		color_vec_ref Separator				= &colors[ImGuiCol_Separator];
		color_vec_ref SeparatorHovered		= &colors[ImGuiCol_SeparatorHovered];
		color_vec_ref SeparatorActive		= &colors[ImGuiCol_SeparatorActive];
		color_vec_ref ResizeGrip			= &colors[ImGuiCol_ResizeGrip];
		color_vec_ref ResizeGripHovered		= &colors[ImGuiCol_ResizeGripHovered];
		color_vec_ref ResizeGripActive		= &colors[ImGuiCol_ResizeGripActive];
		color_vec_ref Tab					= &colors[ImGuiCol_Tab];
		color_vec_ref TabHovered			= &colors[ImGuiCol_TabHovered];
		color_vec_ref TabActive				= &colors[ImGuiCol_TabActive];
		color_vec_ref TabUnfocused			= &colors[ImGuiCol_TabUnfocused];
		color_vec_ref TabUnfocusedActive	= &colors[ImGuiCol_TabUnfocusedActive];
		color_vec_ref DockingPreview		= &colors[ImGuiCol_DockingPreview];
		color_vec_ref DockingEmptyBg		= &colors[ImGuiCol_DockingEmptyBg];
		color_vec_ref PlotLines				= &colors[ImGuiCol_PlotLines];
		color_vec_ref PlotLinesHovered		= &colors[ImGuiCol_PlotLinesHovered];
		color_vec_ref PlotHistogram			= &colors[ImGuiCol_PlotHistogram];
		color_vec_ref PlotHistogramHovered	= &colors[ImGuiCol_PlotHistogramHovered];
		color_vec_ref TableHeaderBg			= &colors[ImGuiCol_TableHeaderBg];
		color_vec_ref TableBorderStrong		= &colors[ImGuiCol_TableBorderStrong];
		color_vec_ref TableBorderLight		= &colors[ImGuiCol_TableBorderLight];
		color_vec_ref TableRowBg			= &colors[ImGuiCol_TableRowBg];
		color_vec_ref TableRowBgAlt			= &colors[ImGuiCol_TableRowBgAlt];
		color_vec_ref TextSelectedBg		= &colors[ImGuiCol_TextSelectedBg];
		color_vec_ref DragDropTarget		= &colors[ImGuiCol_DragDropTarget];
		color_vec_ref NavHighlight			= &colors[ImGuiCol_NavHighlight];
		color_vec_ref NavWindowingHighlight	= &colors[ImGuiCol_NavWindowingHighlight];
		color_vec_ref NavWindowingDimBg		= &colors[ImGuiCol_NavWindowingDimBg];
		color_vec_ref ModalWindowDimBg		= &colors[ImGuiCol_ModalWindowDimBg];
	}colors;
	float &FontGlobalScale = ImGui::GetIO().FontGlobalScale;
};

}