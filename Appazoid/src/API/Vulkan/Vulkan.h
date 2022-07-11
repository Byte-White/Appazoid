#pragma once
#include "Core/AppazoidSpecification.h"
#if AZ_RENDER_API == AZ_RENDER_API_VULKAN

#ifdef _DEBUG
#define IMGUI_VULKAN_DEBUG_REPORT
#endif

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "imgui.h"
#include "vulkan/vulkan.h"
#include <vector>
#include "Logging/Log.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

void check_vk_result(VkResult err);

namespace az
{
	class Vulkan
	{
	public:
		Vulkan() = delete;
		Vulkan(const Vulkan&) = delete;
		void operator=(const Vulkan&) = delete;

		static VkAllocationCallbacks* g_Allocator;
		static VkInstance               g_Instance;
		static VkPhysicalDevice         g_PhysicalDevice;
		static VkDevice                 g_Device;
		static uint32_t                 g_QueueFamily;
		static VkQueue                  g_Queue;
		static VkDebugReportCallbackEXT g_DebugReport;
		static VkPipelineCache          g_PipelineCache;
		static VkDescriptorPool         g_DescriptorPool;
		
		static ImGui_ImplVulkanH_Window g_MainWindowData;
		static int                      g_MinImageCount;
		static bool                     g_SwapChainRebuild;
		static std::vector<std::vector<VkCommandBuffer>> s_AllocatedCommandBuffers;
		static std::vector<std::vector<std::function<void()>>> s_ResourceFreeQueue;
		static uint32_t s_CurrentFrameIndex;

		static void SetupVulkan(const char** extensions, uint32_t extensions_count);
		static void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);
		static void CleanupVulkan();
		static void CleanupVulkanWindow();
		static void VulkanFrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);
		static void VulkanFramePresent(ImGui_ImplVulkanH_Window* wd);
	};

}
#endif