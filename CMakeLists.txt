﻿# CMakeList.txt : CMake project for Appazoid, include source and define
# project specific logic here.
#

project(Appazoid)

add_library(
${PROJECT_NAME}
  STATIC
  #Core
  "src/Core/MemoryTracker.h" 
  "src/Core/MemoryTracker.cpp"
  "src/Core/Base.h"

  #Application
  "src/ApplicationInterface/Application.cpp"
  "src/ApplicationInterface/Application.h"
  "src/ApplicationInterface/ApplicationEntrypoint.cpp"
  #ENTRY POINT
  "src/Core/EntryPoint.h"
  #Logging
  "src/Logging/Log.cpp"
  "src/Logging/Log.h"
  #Graphics(OpenGL)
  "src/Graphics/IndexBuffer.cpp"
  "src/Graphics/VertexArray.cpp"
  "src/Graphics/VertexBuffer.cpp"
  "src/Graphics/Renderer.cpp"
  "src/Graphics/Shader.cpp"
  "src/Graphics/FrameBuffer.cpp"
  #Include folder Stuff
  "include/Appazoid/Appazoid.h"
  "include/Appazoid/UI/Layer.h"
  "include/Appazoid/UI/Image.h"
  
  #STB IMAGE
  "vendor/stb_image/stb_image.h"
  "vendor/stb_image/stb_image.cpp"

  #TEXTURES
 "src/Graphics/Texture.h" 
 "src/Graphics/Texture.cpp" 
 #Specs
 "src/Core/AppazoidSpecification.h"
 "src/Core/PlatformDetection.h" 
 #Window
 "src/ApplicationInterface/Window/WindowHandler.h"
 "src/ApplicationInterface/Window/WindowHandler.cpp"
 "src/ApplicationInterface/Window/WindowStyle.h"
 #UI
 "src/GUI/Gui.h" 
 "src/GUI/Gui.cpp" 
 "src/GUI/ImGuiBuild/imguibuild.cpp"
 #Event System
 "src/Events/Event.h" 
 "src/Events/ApplicationEvent.h"
 "src/Events/MouseEvent.h" 
 "src/Core/KeyCodes.h" 
 "src/Core/MouseCodes.h" 
 #Input
 "src/Core/Input.h" 
 "src/Core/Input.cpp" 
 #LayerStack
 "src/Core/LayerStack.h" 
 "src/Core/LayerStack.cpp" 
 "src/GUI/ImGuiLayer.h" 
 "src/GUI/ImGuiLayer.cpp" 
 #API
 "src/API/Vulkan/Vulkan.cpp"
)

#Appazoid Add Include Directories
target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    #${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/glm # glm is a head-only library so it doesn't need to get linked
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
    $ENV{VULKAN_SDK}/include
)
target_link_directories(
    ${PROJECT_NAME}
    PUBLIC
    $ENV{VULKAN_SDK}/lib
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    vulkan-1.lib
    PUBLIC
    imgui::imgui
    PUBLIC
    glfw
    PUBLIC
    glad::glad
    PUBLIC 
    stb_image::stb_image
    #PUBLIC
    #spdlog::spdlog
)

#find_package(imgui CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)


#find_package(glfw3 CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

#find_package(glad CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)
add_subdirectory("vendor")
add_library(appazoid::appazoid ALIAS ${PROJECT_NAME})
