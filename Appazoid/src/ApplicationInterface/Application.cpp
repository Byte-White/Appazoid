#include "Application.h"
#include "imgui.h"

#include <iostream>
#include <Logging/Log.h>



namespace az 
{

	Application::~Application()
	{

	}
	
	 void ApplicationMain()
	 {

	 }

	void Application::Run()
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
		//render each widget
		for (auto& widget : m_widgets)
		{
			if(widget.second->visible)
				widget.second->OnRender();
		}
	}

	void Application::HideWidget(std::string widget_name)
	{
		if(m_widgets.find(widget_name)!=m_widgets.end())
			this->m_widgets[widget_name]->visible = false;
	}
    void Application::ShowWidget(std::string widget_name)
    {
        if (m_widgets.find(widget_name) != m_widgets.end())
            this->m_widgets[widget_name]->visible = true;
    }

	//-----------------ENTRY POINT-----------------------


    namespace entrypoint
    {
        //helper function for SetColorsTheme()
        const ImVec4 vec3toimguivec4(const glm::vec3& c)
        {
            return ImVec4(c.r, c.g, c.b,1.f);
        }
        void SetColorsTheme() 
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            
            colors[ImGuiCol_Text] = vec3toimguivec4(app->window_style.colors.Text);
            colors[ImGuiCol_TextDisabled] = vec3toimguivec4(app->window_style.colors.TextDisabled);
            colors[ImGuiCol_WindowBg] = vec3toimguivec4(app->window_style.colors.WindowBg);
            colors[ImGuiCol_ChildBg] = vec3toimguivec4(app->window_style.colors.ChildBg);
            colors[ImGuiCol_PopupBg] = vec3toimguivec4(app->window_style.colors.PopupBg);
            colors[ImGuiCol_Border] = vec3toimguivec4(app->window_style.colors.Border);
            colors[ImGuiCol_BorderShadow] = vec3toimguivec4(app->window_style.colors.BorderShadow);
            colors[ImGuiCol_FrameBg] = vec3toimguivec4(app->window_style.colors.FrameBg);
            colors[ImGuiCol_FrameBgHovered] = vec3toimguivec4(app->window_style.colors.FrameBgHovered);
            colors[ImGuiCol_FrameBgActive] = vec3toimguivec4(app->window_style.colors.FrameBgActive);
            colors[ImGuiCol_TitleBg] = vec3toimguivec4(app->window_style.colors.TitleBg);
            colors[ImGuiCol_TitleBgActive] = vec3toimguivec4(app->window_style.colors.TitleBgActive);
            colors[ImGuiCol_TitleBgCollapsed] = vec3toimguivec4(app->window_style.colors.TitleBgCollapsed);
            colors[ImGuiCol_MenuBarBg] = vec3toimguivec4(app->window_style.colors.MenuBarBg);
            colors[ImGuiCol_ScrollbarBg] = vec3toimguivec4(app->window_style.colors.ScrollbarBg);
            colors[ImGuiCol_ScrollbarGrab] = vec3toimguivec4(app->window_style.colors.ScrollbarGrab);
            colors[ImGuiCol_ScrollbarGrabHovered] = vec3toimguivec4(app->window_style.colors.ScrollbarGrabHovered);
            colors[ImGuiCol_ScrollbarGrabActive] = vec3toimguivec4(app->window_style.colors.ScrollbarGrabActive);
            colors[ImGuiCol_CheckMark] = vec3toimguivec4(app->window_style.colors.CheckMark);
            colors[ImGuiCol_SliderGrab] = vec3toimguivec4(app->window_style.colors.SliderGrab);
            colors[ImGuiCol_SliderGrabActive] = vec3toimguivec4(app->window_style.colors.SliderGrabActive);
            colors[ImGuiCol_Button] = vec3toimguivec4(app->window_style.colors.Button);
            colors[ImGuiCol_ButtonHovered] = vec3toimguivec4(app->window_style.colors.ButtonHovered);
            colors[ImGuiCol_ButtonActive] = vec3toimguivec4(app->window_style.colors.ButtonActive);
            colors[ImGuiCol_Header] = vec3toimguivec4(app->window_style.colors.Header);
            colors[ImGuiCol_HeaderHovered] = vec3toimguivec4(app->window_style.colors.HeaderHovered);
            colors[ImGuiCol_HeaderActive] = vec3toimguivec4(app->window_style.colors.HeaderActive);
            colors[ImGuiCol_Separator] = vec3toimguivec4(app->window_style.colors.Separator);
            colors[ImGuiCol_SeparatorHovered] = vec3toimguivec4(app->window_style.colors.SeparatorHovered);
            colors[ImGuiCol_SeparatorActive] = vec3toimguivec4(app->window_style.colors.SeparatorActive);
            colors[ImGuiCol_ResizeGrip] = vec3toimguivec4(app->window_style.colors.ResizeGrip);
            colors[ImGuiCol_ResizeGripHovered] = vec3toimguivec4(app->window_style.colors.ResizeGripHovered);
            colors[ImGuiCol_ResizeGripActive] = vec3toimguivec4(app->window_style.colors.ResizeGripActive);
            colors[ImGuiCol_Tab] = vec3toimguivec4(app->window_style.colors.Tab);
            colors[ImGuiCol_TabHovered] = vec3toimguivec4(app->window_style.colors.TabHovered);
            colors[ImGuiCol_TabActive] = vec3toimguivec4(app->window_style.colors.TabActive);
            colors[ImGuiCol_TabUnfocused] = vec3toimguivec4(app->window_style.colors.TabUnfocused);
            colors[ImGuiCol_TabUnfocusedActive] = vec3toimguivec4(app->window_style.colors.TabUnfocusedActive);
            colors[ImGuiCol_DockingPreview] = vec3toimguivec4(app->window_style.colors.DockingPreview);
            colors[ImGuiCol_DockingEmptyBg] = vec3toimguivec4(app->window_style.colors.DockingEmptyBg);
            colors[ImGuiCol_PlotLines] = vec3toimguivec4(app->window_style.colors.PlotLines);
            colors[ImGuiCol_PlotLinesHovered] = vec3toimguivec4(app->window_style.colors.PlotLinesHovered);
            colors[ImGuiCol_PlotHistogram] = vec3toimguivec4(app->window_style.colors.PlotHistogram);
            colors[ImGuiCol_PlotHistogramHovered] = vec3toimguivec4(app->window_style.colors.PlotHistogramHovered);
            colors[ImGuiCol_TableHeaderBg] = vec3toimguivec4(app->window_style.colors.TableHeaderBg);
            colors[ImGuiCol_TableBorderStrong] = vec3toimguivec4(app->window_style.colors.TableBorderStrong);
            colors[ImGuiCol_TableBorderLight] = vec3toimguivec4(app->window_style.colors.TableBorderLight);
            colors[ImGuiCol_TableRowBg] = vec3toimguivec4(app->window_style.colors.TableRowBg);
            colors[ImGuiCol_TableRowBgAlt] = vec3toimguivec4(app->window_style.colors.TableRowBgAlt);
            colors[ImGuiCol_TextSelectedBg] = vec3toimguivec4(app->window_style.colors.TextSelectedBg);
            colors[ImGuiCol_DragDropTarget] = vec3toimguivec4(app->window_style.colors.DragDropTarget);
            colors[ImGuiCol_NavHighlight] = vec3toimguivec4(app->window_style.colors.NavHighlight);
            colors[ImGuiCol_NavWindowingHighlight] = vec3toimguivec4(app->window_style.colors.NavWindowingHighlight);
            colors[ImGuiCol_NavWindowingDimBg] = vec3toimguivec4(app->window_style.colors.NavWindowingDimBg);
            colors[ImGuiCol_ModalWindowDimBg] = vec3toimguivec4(app->window_style.colors.ModalWindowDimBg);

            // IO

            ImGuiIO& io = ImGui::GetIO();

            io.FontGlobalScale = app->window_style.FontGlobalScale;
        }

        //useless function
        static void Bounce(float& colour, float& increment)
        {
            if (colour > 1.0f || colour < 0.0f)
                increment = -increment;
        }
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

        int create_window()
        {

            // Create a GLFWwindow object
            window = glfwCreateWindow(app->window_style.width, app->window_style.height, app->window_style.title.c_str(), NULL, NULL);
            // Error check if the window fails to create
            if (window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            // Introduce the window into the current context
            glfwMakeContextCurrent(window);

            //Load GLAD so it configures OpenGL
            gladLoadGL();
            //Enable OpenGL Error Message Callback
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(MessageCallback, nullptr);
            // Specify the viewport of OpenGL in the Window
            // In this case the viewport goes from x = 0, y = 0, to x = width, y = height
            glViewport(0, 0, app->window_style.width, app->window_style.height);
            return 0;
        }
        void init_imgui()
        {
            // Initialize ImGUI
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
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
            case az::StyleColor::CustomStyleColors:
                SetColorsTheme();
                break;
            }
        }
        void Main(int argc, char** argv)
        {
            // Main while loop
            while (!glfwWindowShouldClose(window) && (!app->done))
            {
                // Specify the color of the background
                glClearColor(app->clear_color[0], app->clear_color[1], app->clear_color[2], app->clear_color[3]);
                // Clean the back buffer and assign the new color to it
                app->renderer.Clear();//glClear(GL_COLOR_BUFFER_BIT);

                // Tell OpenGL a new frame is about to begin
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

                // ImGuiWindowFlags_NoDocking flag is used to make the parent window not dockable ,
                // because it would be confusing to have two docking targets within each others.
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
                if (app->m_MenubarCallback)
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
                ImGui::Begin((app->window_style.title + " DockSpace").c_str(), nullptr, window_flags);
                ImGui::PopStyleVar();

                ImGui::PopStyleVar(2);

                if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
                {
                    ImGuiID dockspace_id = ImGui::GetID((app->window_style.title + " DockSpace").c_str());
                    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
                }
                //Entry Point
                app->Run();
                //Entry Point

                ImGui::End();
                // Renders the ImGUI elements
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                
                // Swap the back buffer with the front buffer
                glfwSwapBuffers(window);
                // Take care of all GLFW events
                glfwPollEvents();
                // Update and Render additional Platform Windows
                if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                    GLFWwindow* backup_current_context = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backup_current_context);
                }
            }
        }
        void cleanup()
        {
            // Deletes all ImGUI instances
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            // Delete window before ending the program
            glfwDestroyWindow(window);
            // Terminate GLFW before ending the program
            glfwTerminate();


            delete app;//free the allocated memory
        }
    }
}