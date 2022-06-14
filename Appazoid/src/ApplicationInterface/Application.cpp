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
    using az::entrypoint::io;

    Application::Application(WindowStyle& style) 
        :window_style(style), done(false)
    {
        //Todo: premesti create_window tuk i mahni oniq shibani funkcii
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
    static bool event_callbacks_set = false;
    void Application::Run()
    {
        if (!event_callbacks_set)
        {
            window_handler->SetEventCallback(AZ_BIND_EVENT_FN(Application::OnEvent));
            event_callbacks_set = true;
        }
        this->Clear();
        this->NewFrame();
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
        // Take care of all GLFW events
        glfwPollEvents();
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

    void Application::OnEvent(Event& e)
    {
        //APPAZOID_CORE_WARN("ON EVENT");
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(AZ_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(AZ_BIND_EVENT_FN(Application::OnWindowResize));

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
    
	//-----------------ENTRY POINT-----------------------


    namespace entrypoint
    {

        GLFWwindow* window;
        Application* app;
        ImGuiIO* io;

        void init_glfw()
        {
            // Initialize GLFW
            glfwInit();

            // Tell GLFW what version of OpenGL we are using 
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            // Tell GLFW to enable DEBUG OUTPUT
            //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
            // Tell GLFW we are using the CORE profile
            // So that means we only have the modern functions
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        }
        //Error Message Callback
        void GLAPIENTRY
            MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam)
        {
            APPAZOID_CORE_ERROR("GL CALLBACK: {0} type = {1}, severity = {2}, message = {3}", 
                (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                type, severity, message);
            //fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            //    (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            //    type, severity, message);
        }

        void init_glad()
        {
            APPAZOID_CORE_INFO("(GLAD)Loading OpenGL...");
            //Load GLAD so it configures OpenGL
            gladLoadGL();
            //Enable OpenGL Error Message Callback
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(MessageCallback, nullptr);
        }



        int create_window()
        {
            // Create a window with WindowHandler
            app->window_handler = az::make_scope<WindowHandler>(app->window_style);
            window = app->window_handler->GetGLFWWindow();
            // Error check if the window fails to create
            if (window == NULL)
            {
                APPAZOID_CORE_ERROR("Failed to create GLFW window");
                //std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            // Introduce the window into the current context
            glfwMakeContextCurrent(window);
            init_glad();
            // Specify the viewport of OpenGL in the Window
            // In this case the viewport goes from x = 0, y = 0, to x = width, y = height
            glViewport(0, 0, app->window_style.width, app->window_style.height);
            az::Input::SetWindow(az::entrypoint::app->window_handler->GetGLFWWindow());//Selects Window

            return 0;
        }
        void init_imgui()
        {
            io = &ImGui::GetIO(); (void)io;

            //ImGui Flags (Enabled By Default)
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            //io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows ///Has Problems With OpenGl3
            
            io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
            
            if(app->m_ConfigFlagsCallback!=nullptr)
            app->m_ConfigFlagsCallback(*io);// Set IMGUI FLAGS

            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");

            switch (app->window_style.stylecolor)
            {
            case az::StyleColor::StyleColorDark:
                ImGui::StyleColorsDark();
                break;
            case az::StyleColor::StyleColorLight:
                ImGui::StyleColorsLight();
                break;
            case az::StyleColor::StyleColorClassic:
                ImGui::StyleColorsClassic();
                break;
            //case az::StyleColor::CustomStyleColors:
                //SetColorsTheme(app);
            //    break;
            }
        }
        void Main(int argc, char** argv)
        {
            //OnConstruction function for all layers
            for (auto widget : app->GetLayerStack())
            {
                widget.second->OnConstruction();
            }
            //random shit for FrameBufferTesting
            // GLuint fbo;
            // Texture* texture;
            // 
            // Main while loop

            while (!glfwWindowShouldClose(window) && (!app->done))
            {
                app->Run();
            }
        }
        void cleanup()
        {
            // Calls the "Destructor"(Before Cleaning up)
            for (auto widget : app->GetLayerStack())
            {
                widget.second->OnDestruction();
            }
            // Deletes all ImGUI instances
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            // Delete window before ending the program
            app->window_handler->DestroyWindow();
            // Terminate GLFW before ending the program
            glfwTerminate();


            delete app;//free the allocated memory
        }
    }
}