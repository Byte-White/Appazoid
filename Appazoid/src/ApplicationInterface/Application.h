#pragma once
//#ifndef APPAZOID_APPLICATION_H
//#define APPAZOID_APPLICATION_H
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include "Appazoid/UI/Widget.h"

#include "imgui.h"
#ifndef BACKENDS
#define BACKENDS
#include "backends/imgui_impl_opengl3.h"
#endif 
#include "backends/imgui_impl_glfw.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h> 




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

	class Application
	{
	private:
		int widget_naming_count=0;// helps to make a default name (example: widget_123)
	public:
		bool done;
		float clear_color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
		struct WindowStyle
		{
			int width, height;
			std::string title;
			enum StyleColor
			{
				StyleColorDark=0, StyleColorLight, StyleColorClassic
			}stylecolor = StyleColorDark;
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
			if (widget_name == "")widget_name = "widget_"+widget_naming_count;
			static_assert(std::is_base_of<Widget, T>::value, "Added type should be a subclass of az::Widget");
			this->m_widgets[widget_name]=(std::make_shared<T>(args...));
			//->OnConstruction();
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
		std::function<void(ImGuiIO&)> m_ConfigFlagsCallback;
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