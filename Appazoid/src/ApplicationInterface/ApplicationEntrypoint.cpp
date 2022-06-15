#include "Application.h"
//-----------------ENTRY POINT-----------------------

namespace az
{
    namespace entrypoint
    {
        extern ImGuiIO* io;

        extern GLFWwindow* window;
        extern az::Application* app;
        extern ImGuiIO* io;

        void init_glfw()
        {
            static bool init_glfw = false;
            if (init_glfw) return;
            init_glfw = true;

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
            static bool init_glad = false;
            if (init_glad) return;
            init_glad = true;
            APPAZOID_CORE_INFO("(GLAD)Loading OpenGL...");
            //Load GLAD so it configures OpenGL
            gladLoadGL();
            //Enable OpenGL Error Message Callback
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(MessageCallback, nullptr);
        }


        void init_imgui()
        {
            static bool init_imgui = false;
            if (init_imgui) return;
            init_imgui = true;

            io = &ImGui::GetIO(); (void)io;

            //ImGui Flags (Enabled By Default)
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            //io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows ///Has Problems With OpenGl3

            io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

            if (app->m_ConfigFlagsCallback != nullptr)
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