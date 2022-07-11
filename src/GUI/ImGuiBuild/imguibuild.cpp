//Used to build imgui impl files
#include "Core/AppazoidSpecification.h"
#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
#include "backends/imgui_impl_opengl3.cpp"
#elif AZ_RENDER_API == AZ_RENDER_API_VULKAN
#include "backends/imgui_impl_vulkan.cpp"
#endif
#include "backends/imgui_impl_glfw.cpp"