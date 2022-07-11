#pragma once
//#ifndef APPAZOID_APPLICATION_H
//#define APPAZOID_APPLICATION_H
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <future>

#include "Core/Base.h"
#include "Core/AppazoidSpecification.h"

#include "Appazoid/UI/Layer.h"

#include "imgui.h"
#ifndef AZ_IMGUI_BACKENDS

#define AZ_IMGUI_BACKENDS

#include "backends/imgui_impl_glfw.h"

#if AZ_RENDER_API == AZ_RENDER_API_OPENGL//(az::RenderAPI::API::OpenGL)
#include "backends/imgui_impl_opengl3.h"
#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN//az::RenderAPI::API::Vulkan
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "backends/imgui_impl_vulkan.h"
#else
#error "No Render API Selected"
#endif

#endif
#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h> 
#include "API/Vulkan/Vulkan.h"
#include "GUI/ImGuiLayer.h"

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

#include "Core/Input.h"
#include "Core/LayerStack.h"


#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Core/MemoryTracker.h"

namespace az {

	//Config Helper Functions
	inline void EnableConfigFlag(ImGuiIO& io, ImGuiConfigFlags_ flag)		{ io.ConfigFlags |= flag;	}
	inline void DisableConfigFlag(ImGuiIO& io, ImGuiConfigFlags_ flag)		{ io.ConfigFlags &= ~flag;	}

	inline void EnableWindowFlag(ImGuiWindowFlags&  wf, ImGuiWindowFlags_ flag)			{ wf |= flag;	}
	inline void DisableWindowFlag(ImGuiWindowFlags& wf, ImGuiWindowFlags_ flag)			{ wf &= ~flag;	}

	//MACROS FOR FLAG CONFIGURING (backup)
	//#define ENABLE_CONFIG_FLAGS	(_io,_flag)		_io->ConfigFlags |=	_flag
	//#define DISABLE_CONFIG_FLAGS(_io,_flag)		_io->ConfigFlags &= ^_flag

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

		void init_glfw();
		void init_render_api();
		void init_imgui();
		void Main(int argc, char** argv);
		void cleanup();
	}
	
	class Application
	{
	private:
		int layer_naming_count	=0;// helps to make a default name (example: layer_123)
		int overlay_naming_count=0;// helps to make a default name (example: overlay_123)
		bool m_Minimized = false;
	public:
		Renderer renderer;
		bool done;
		glm::vec4 clear_color = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };//float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

		WindowStyle window_style;
		az::Ref<WindowHandler> window_handler;
	public:
		Application(WindowStyle& style /*= WindowStyle(255, 255, "Appazoid Application") */);
		Application() {}
		virtual ~Application();
		void Create(WindowStyle& style);
		static Application* Get() { return s_Instance; }
		virtual void RenderUI();
		virtual void EventPolling();
		az::Ref<WindowHandler> GetWindow() { return window_handler; }
		//main application loop
		virtual void Run();
		virtual void OnStart();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		inline bool IsMinimized() { return m_Minimized; }
		void Clear();
		//Creates a dockspace
		void BeginDockspace(std::string dockspace_name="");
		void EndDockspace();

		template<typename T, typename ...T_args>
		inline void AddLayer(std::string layer_name,T_args&... args)
		{
			if (layer_name == "") { layer_name += "layer_"+ std::to_string(layer_naming_count++);}//layer default naming
			static_assert(std::is_base_of<Layer, T>::value, "Added type should be a subclass of az::Layer");
			this->m_layerstack.PushLayer(layer_name,az::make_ref<T>(args...));
		}
		template<typename T, typename ...T_args>
		inline void AddOverlay(std::string overlay_name, T_args&... args)
		{
			if (overlay_name == "") { overlay_name += "overlay_" + std::to_string(overlay_naming_count++); }//overlay default naming
			static_assert(std::is_base_of<Layer, T>::value, "Added type should be a subclass of az::Layer");
			this->m_layerstack.PushOverlay(overlay_name, az::make_ref<T>(args...));
		}

		inline LayerStack& GetLayerStack()
		{
			return m_layerstack;
		}

		inline void AddMenubarCallback(std::function<void()> function) { m_MenubarCallback = function; }
		inline void AddConfigFlagCallback(std::function<void(ImGuiIO& io)> function) { m_ConfigFlagsCallback=function; }
		inline void Close() { done = true; }
		void HideLayer(std::string layer_name);
		void ShowLayer(std::string layer_name);
		//std::vector<std::string> GetLayersNames();
		friend void entrypoint::init_imgui();//allows imgui initialization to use callback functions
		friend void entrypoint::Main(int argc, char** argv);
		friend class ImGuiLayer;
	private:
		std::function<void()> m_MenubarCallback;//menubar callback function pointer
		std::function<void(ImGuiIO&)> m_ConfigFlagsCallback;// Configure Flags callback
		//Scope<std::thread> event_polling_thread;
		Scope<std::thread> rendering_thread;
		static Application* s_Instance;

		LayerStack m_layerstack;
		ImGuiLayer* m_imguilayer;
	};
	//To be defined in CLIENT
	Application* CreateApplication(int,char**);


    namespace entrypoint
    {
		extern Application* app;
		/// Some Variables are defined in the beginning of
		/// The main namespace
		//void SetColorsTheme(az::Application* app);
    }

	using entrypoint::app;

}

//#endif