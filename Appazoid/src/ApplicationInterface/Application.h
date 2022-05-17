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

#include "Window/WindowHandler.h"
#include "Window/WindowStyle.h"


#include "Graphics/IndexBuffer.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/FrameBuffer.h"



namespace az {

	//Config Helper Functions
	inline void EnableConfigFlag(ImGuiIO& io, ImGuiConfigFlags_ flag)		{ io.ConfigFlags |= flag;	}
	inline void DisableConfigFlag(ImGuiIO& io, ImGuiConfigFlags_ flag)		{ io.ConfigFlags &= ~flag;	}

	inline void EnableWindowFlag(ImGuiWindowFlags&  wf, ImGuiWindowFlags_ flag)			{ wf |= flag;	}
	inline void DisableWindowFlag(ImGuiWindowFlags& wf, ImGuiWindowFlags_ flag)			{ wf &= ~flag;	}

	//MONITOR RESOLUTION
	inline glm::ivec2 GetMonitorResolution() 
	{ return glm::ivec2{ glfwGetVideoMode(glfwGetPrimaryMonitor())->width,glfwGetVideoMode(glfwGetPrimaryMonitor())->height }; }
	
	inline int GetMonitorWidth()	{ return GetMonitorResolution().x; }
	inline int GetMonitorHeight()	{ return GetMonitorResolution().y; }
	
	//static LPCTSTR windows_title = _T("My App");
	//static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	namespace entrypoint
	{ 
		//extern GLFWwindow* window;
		extern ImGuiIO* io;
	}
	
	class Application
	{
	private:
		int widget_naming_count=0;// helps to make a default name (example: widget_123)
	public:
		Renderer renderer;
		bool done;
		glm::vec4 clear_color = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };//float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

		WindowStyle window_style;//was const
		std::unique_ptr<WindowHandler> window_handler;
	public:
		Application(WindowStyle& style = WindowStyle(255, 255, "Appazoid Application"))
			:window_style(style),done(false)
		{}
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