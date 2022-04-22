#pragma once
#include "ApplicationInterface/Application.h"

extern az::Application* az::CreateApplication(int,char**);


#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


namespace az
{
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
            // In this case we are using OpenGL 3.3
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            // Tell GLFW we are using the CORE profile
            // So that means we only have the modern functions
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        }
        int create_window()
        {

            // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
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
            // Specify the viewport of OpenGL in the Window
            // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
            glViewport(0, 0, app->window_style.width, app->window_style.height);
            return 0;
        }
        void init_imgui()
        {
            // Initialize ImGUI
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            io = &ImGui::GetIO(); (void)io;
            io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
            io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
            
            switch (app->window_style.stylecolor)
            {
            case Application::WindowStyle::StyleColorDark:
                ImGui::StyleColorsDark();
                break;
            case Application::WindowStyle::StyleColorLight:
                ImGui::StyleColorsLight();
                break;
            case Application::WindowStyle::StyleColorClassic:
                ImGui::StyleColorsClassic();
                break;
            }
            
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }
        void Main(int argc,char**argv)
        {
            // Main while loop
            while (!glfwWindowShouldClose(window) && (!app->done))
            {
                // Specify the color of the background
                glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
                // Clean the back buffer and assign the new color to it
                glClear(GL_COLOR_BUFFER_BIT);

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
                    ImGuiID dockspace_id = ImGui::GetID((app->window_style.title + "DockSpace").c_str());
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

/*static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}*/
#ifndef AZ_CUSTOM_MAIN
int main(int argc,char** argv)
{
    az::entrypoint::app = az::CreateApplication(argc,argv);

    az::entrypoint::init_glfw();

    az::entrypoint::create_window();
    az::entrypoint::init_imgui();

    az::entrypoint::Main(argc,argv);

    az::entrypoint::cleanup();
    return 0;
}
#endif