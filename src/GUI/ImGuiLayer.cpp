#include "ImGuiLayer.h"
#include "ApplicationInterface/Application.h"
#include "API/Vulkan/Vulkan.h"
#include "API/Vulkan/Vulkan.cpp"
namespace az
{
	void ImGuiLayer::OnConstruction()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		Application::Get()->m_ConfigFlagsCallback(ImGui::GetIO());
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			
		}
		
		
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(Application::Get()->GetWindow()->GetGLFWWindow(), true);
		#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
		ImGui_ImplOpenGL3_Init("#version 410");
		#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN
		// Create Framebuffers
		int w, h;
		// Create Window Surface
		VkSurfaceKHR surface;
		VkResult err = glfwCreateWindowSurface(Vulkan::g_Instance, Application::Get()->window_handler->GetGLFWWindow(), Vulkan::g_Allocator, &surface);
		check_vk_result(err);

		glfwGetFramebufferSize(Application::Get()->window_handler->GetGLFWWindow(), &w, &h);
		ImGui_ImplVulkanH_Window* wd = &Vulkan::g_MainWindowData;
		az::Vulkan::SetupVulkanWindow(wd, surface, w, h);

		Vulkan::s_AllocatedCommandBuffers.resize(wd->ImageCount);
		Vulkan::s_ResourceFreeQueue.resize(wd->ImageCount);

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForVulkan(Application::Get()->window_handler->GetGLFWWindow(), true);
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = Vulkan::g_Instance;
		init_info.PhysicalDevice = Vulkan::g_PhysicalDevice;
		init_info.Device = Vulkan::g_Device;
		init_info.QueueFamily = Vulkan::g_QueueFamily;
		init_info.Queue = Vulkan::g_Queue;
		init_info.PipelineCache = Vulkan::g_PipelineCache;
		init_info.DescriptorPool = Vulkan::g_DescriptorPool;
		init_info.Subpass = 0;
		init_info.MinImageCount = Vulkan::g_MinImageCount;
		init_info.ImageCount = wd->ImageCount;
		init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
		init_info.Allocator = Vulkan::g_Allocator;
		init_info.CheckVkResultFn = check_vk_result;
		ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);
		#endif
	}

	void ImGuiLayer::OnDestruction()
	{
		#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
		ImGui_ImplOpenGL3_Shutdown();
		#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN
		ImGui_ImplVulkan_Shutdown();
		#endif
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}
	
	void ImGuiLayer::Begin()
	{
		#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
		ImGui_ImplOpenGL3_NewFrame();
		#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN
		ImGui_ImplVulkan_NewFrame();
		#endif
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	void ImGuiLayer::End()
	{

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)Application::Get()->GetWindow()->GetWidth(),
			(float)Application::Get()->GetWindow()->GetHeight());

		// Rendering
		ImGui::Render();
		#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN

		#endif
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}