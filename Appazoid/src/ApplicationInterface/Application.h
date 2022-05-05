#pragma once
//#ifndef APPAZOID_APPLICATION_H
//#define APPAZOID_APPLICATION_H
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include "Core/AppazoidSpecification.h"

#include "Appazoid/UI/Widget.h"

#include "imgui.h"
#ifndef AZ_IMGUI_BACKENDS
#define AZ_IMGUI_BACKENDS
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#endif 
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "Appazoid/UI/Image.h"

#include "Graphics/IndexBuffer.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/FrameBuffer.h"




namespace az {

	inline void EnableConfigFlag(ImGuiIO& io, ImGuiConfigFlags_ flag)		{ io.ConfigFlags |= flag;	}
	inline void DisableConfigFlag(ImGuiIO& io, ImGuiConfigFlags_ flag)		{ io.ConfigFlags &= ~flag;	}

	inline void EnableWindowFlag(ImGuiWindowFlags&  wf, ImGuiWindowFlags_ flag)			{ wf |= flag;	}
	inline void DisableWindowFlag(ImGuiWindowFlags& wf, ImGuiWindowFlags_ flag)			{ wf &= ~flag;	}

	//static LPCTSTR windows_title = _T("My App");
	//static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	namespace entrypoint
	{ 
		extern GLFWwindow* window;
		extern ImGuiIO* io;
	}
	enum class StyleColor
	{
		CustomStyleColors = 0, StyleColorDark, StyleColorLight, StyleColorClassic
	};
	class Application
	{
	private:
		int widget_naming_count=0;// helps to make a default name (example: widget_123)
	public:
		Renderer renderer;
		bool done;
		glm::vec4 clear_color = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };//float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		struct WindowStyle
		{
			int width, height;
			std::string title;
			StyleColor stylecolor = StyleColor::CustomStyleColors;
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
		const WindowStyle window_style;
	public:
		Application(const WindowStyle& style = {255,255,"Appazoid Application"})
			:window_style(style),done(false)
		{};
		~Application();
		void Run();
		/* AddWidget worse function(backup)
		template<typename T>
		inline void AddWidget(const std::shared_ptr<T>& _widget, std::string widget_name)
		{
			this->m_widgets[widget_name] = (std::make_shared<T>());
			
			//Widget(_widget).OnConstruction();
		};
		*/

		template<typename T, typename ...T_args>
		inline void AddWidget(std::string widget_name,T_args&... args)
		{
			if (widget_name == "") {widget_name += "widget_"+ std::to_string(widget_naming_count++);}//widget default naming
			static_assert(std::is_base_of<Widget, T>::value, "Added type should be a subclass of az::Widget");
			this->m_widgets[widget_name]=(std::make_shared<T>(args...));
			//this->m_widgets[widget_name]->OnConstruction();
			//TODO: dobavi izvikvane na ->OnConstruction();
		}

		inline std::unordered_map<std::string, std::shared_ptr<Widget>>& GetWidgetList()
		{
			return m_widgets;
		}

		inline void AddMenubarCallback(std::function<void()> function) { m_MenubarCallback = function; }
		inline void AddConfigFlagCallback(std::function<void(ImGuiIO& io)> function) { m_ConfigFlagsCallback=function; }
		inline void Close() { done = true; }
		void HideWidget(std::string widget_name);
		void ShowWidget(std::string widget_name);
		//std::vector<std::string> GetWidgetsNames();
	public:
		std::function<void()> m_MenubarCallback;//menubar callback function pointer
		std::function<void(ImGuiIO&)> m_ConfigFlagsCallback;// Configure Flags callback
	private:
		//std::vector<std::shared_ptr<Widget>> m_widgets;
		std::unordered_map<std::string,std::shared_ptr<Widget>> m_widgets;//hash map(name:widget)
	};
	//To be defined in CLIENT
	Application* CreateApplication(int,char**);


    namespace entrypoint
    {
		extern Application* app;
		/// Some Variables are defined in the beginning of
		/// The main namespace
		void init_glfw();
		void init_glad();
		int create_window();
		void init_imgui();
        void Main(int argc, char** argv);
        void cleanup();
    }

}
//MACROS FOR FLAG CONFIGURING (backup)
//#define ENABLE_CONFIG_FLAGS	(_io,_flag)		_io->ConfigFlags |=	_flag
//#define DISABLE_CONFIG_FLAGS(_io,_flag)		_io->ConfigFlags &= ^_flag

//#endif