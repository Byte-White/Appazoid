#include "Application.h"
//-----------------ENTRY POINT-----------------------
#include "Core/EntryPoint.h"

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

        void init_render_api()
        {
            static bool init_render_api = false;
            if (init_render_api) return;
            init_render_api = true;

            #if AZ_RENDER_API == AZ_RENDER_API_OPENGL
            APPAZOID_CORE_INFO("(GLAD)Loading OpenGL...");
            //Load GLAD so it configures OpenGL
            gladLoadGL();
            //Enable OpenGL Error Message Callback
            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(MessageCallback, nullptr);
            #elif AZ_RENDER_API == AZ_RENDER_API_VULKAN
            APPAZOID_CORE_INFO("Initializing Vulkan...");
            if (!glfwVulkanSupported())
            {
                APPAZOID_CORE_ERROR("GLFW: Vulkan not supported!\n");
                return;
            }

            uint32_t extensions_count = 0;
            const char** extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
            Vulkan::SetupVulkan(extensions, extensions_count);

            
            #endif
        }


        void init_imgui()
        {
            static bool init_imgui = false;
            if (init_imgui) return;
            init_imgui = true;
            
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
            // Take care of all events polling
            //app->EventPolling();
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

            //app->EventPolling();

            //std::thread t();
            //auto eventhandler = std::async(&Application::EventPolling,entrypoint::app);
            while (!app->done)
            {
                app->Run();
                app->EventPolling();
            }
            app->done = true;
            //t.join();
            //app->rendering_thread->join();
            //app->event_polling_thread->join();
        }
        void cleanup()
        {
            // Calls the "Destructor"(Before Cleaning up)
            for (auto widget : app->GetLayerStack())
            {
                widget.second->OnDestruction();
            }

            // Delete window before ending the program
            app->window_handler->DestroyWindow();
            // Terminate GLFW before ending the program
            #if AZ_RENDER_API == AZ_RENDER_API_VULKAN

            // Cleanup
            VkResult err = vkDeviceWaitIdle(Vulkan::g_Device);
            check_vk_result(err);

            // Free resources in queue
            for (auto& queue : Vulkan::s_ResourceFreeQueue)
            {
                for (auto& func : queue)
                    func();
            }
            Vulkan::s_ResourceFreeQueue.clear();

            ImGui_ImplVulkan_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            Vulkan::CleanupVulkanWindow();
            Vulkan::CleanupVulkan();
            #endif
            glfwTerminate();


            delete app;//free the allocated memory
        }
    }
}