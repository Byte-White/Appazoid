#include "Application.h"
#include "imgui.h"

#include <iostream>
#include <Logging/Log.h>

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"



namespace az 
{
    namespace entrypoint
    {
        GLFWwindow* window;
        Application* app;
        ImGuiIO* io;
    }
    using az::entrypoint::io;

    Application::Application(WindowStyle& style) 
        :window_style(style)
    {
        Create(style);
    }

    void Application::Create(WindowStyle& style)
    {
        // Create a window with WindowHandler
        window_handler = az::make_scope<WindowHandler>(style);

        entrypoint::window = window_handler->GetGLFWWindow();
        // Error check if the window fails to create
        if (entrypoint::window == NULL)
        {
            APPAZOID_CORE_CRITICAL("Failed to create a window!");
            glfwTerminate();
            throw "Failed to create a window!";
        }
        // Introduce the window into the current context
        glfwMakeContextCurrent(entrypoint::window);
        entrypoint::init_glad();
        // Specify the viewport of OpenGL in the Window
        // In this case the viewport goes from x = 0, y = 0, to x = width, y = height
        glViewport(0, 0, style.width, style.height);
        az::Input::SetWindow(window_handler->GetGLFWWindow());//Selects Window
        done = false;

        //Event Callback Function
        window_handler->SetEventCallback(AZ_BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
	{

	}
	
	void Application::RenderUI()
	{
		//menubar
		if (m_MenubarCallback)
		{
			if (ImGui::BeginMenuBar())
			{
				m_MenubarCallback();
				ImGui::EndMenuBar();
			}
		}
		//render each layer
		for (auto& layer : m_layerstack)
		{
			if(layer.second->visible)
				layer.second->OnUIRender();
		}
	}

    void Application::EventPolling()
    {
        //APPAZOID_CORE_DEBUG("GLFW POLL EVENTS");
        glfwPollEvents();
    }

    void Application::Run()
    {
        this->NewFrame();
        this->Clear();
        this->BeginDockspace();
        //Entry Point
        this->RenderUI();
        //Entry Point

        // Renders the ImGUI elements
        //here
        this->EndDockspace();
        this->RenderFrame();


        // Swap the back buffer with the front buffer
        //here
        //random stuff

        this->window_handler->SwapBuffers();
        for (auto layer : this->GetLayerStack())
        {
            layer.second->OnBufferSwap();
        }

        // Update and Render additional Platform Windows
        // Only when Multi-Viewports are enabled
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
    }

    void Application::OnStart()
    {
        app->rendering_thread = az::make_scope<std::thread>(AZ_BIND_FN(Application::EventPolling));
        //app->event_polling_thread = az::make_scope<std::thread>(AZ_BIND_FN(EventPolling));
    }

    void Application::OnEvent(Event& e)
    {
        //APPAZOID_CORE_WARN("ON EVENT");
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(AZ_BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(AZ_BIND_EVENT_FN(OnWindowResize));

        for (auto it = m_layerstack.rbegin(); it != m_layerstack.rend(); ++it)
        {
            
            if (e.Handled)
                break;
            (*it).second->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        //APPAZOID_CORE_INFO("OnWindowClose");
        done = true;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        //APPAZOID_CORE_INFO("OnWindowResize");
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::Clear()
    {
        // Specify the color of the background
        glClearColor(this->clear_color.r, this->clear_color.g, this->clear_color.b, this->clear_color.a);
        // Clean the back buffer and assign the new color to it
        this->renderer.Clear();//glClear(GL_COLOR_BUFFER_BIT);
    }

    void Application::NewFrame()
    {
        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }


    void Application::BeginDockspace(std::string dockspace_name)
    {
        using az::entrypoint::io;
        if (dockspace_name == "") dockspace_name = this->window_style.title;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // ImGuiWindowFlags_NoDocking flag is used to make the parent window not dockable ,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        if (this->m_MenubarCallback)
            window_flags |= ImGuiWindowFlags_MenuBar;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render the background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin((this->window_style.title + " DockSpace").c_str(), nullptr, window_flags);
        ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID((dockspace_name + " DockSpace").c_str());
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }
    
    void Application::EndDockspace()
    {
        ImGui::End();
    }

    void Application::RenderFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    /*
    void Application::ReloadColorTheme()
    {
        //entrypoint::SetColorsTheme(this);
    }*/
    
	void Application::HideLayer(std::string layer_name)
	{
        auto it = m_layerstack.find(layer_name);
		if(it!=m_layerstack.end())
			it->second->visible = false;
	}
    
    void Application::ShowLayer(std::string layer_name)
    {
        auto it = m_layerstack.find(layer_name);
        if (it != m_layerstack.end())
            it->second->visible = true;
    }
}