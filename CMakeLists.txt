# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.6)

project (AppazoidTestProject)

# Include sub-projects.
#add_subdirectory("ImGui")

#1 == AZ_RENDER_API_OPENGL
#2 == AZ_RENDER_API_VULKAN
add_compile_definitions(AZ_RENDER_API=AZ_RENDER_API_OPENGL)
add_subdirectory ("Appazoid")
add_subdirectory ("Test")