# CMakeList.txt : CMake project for Appazoid, include source and define
# project specific logic here.
#

project(Appazoid)

add_library(
${PROJECT_NAME}
  STATIC
  #src stuff
  "src/ApplicationInterface/Application.cpp"
  "src/ApplicationInterface/Application.h"
  "src/Logging/Log.cpp"
  "src/Logging/Log.h"
  #OpenGL stuff
  "src/Graphics/IndexBuffer.cpp"
  "src/Graphics/VertexArray.cpp"
  "src/Graphics/VertexBuffer.cpp"
  "src/Graphics/Renderer.cpp"
  "src/Graphics/Shader.cpp"
  "src/Graphics/FrameBuffer.cpp"
  #Include folder Stuff
  "include/Appazoid/Appazoid.h"
  "include/Appazoid/UI/widget.h"
  "include/Appazoid/UI/Image.h"
  
  #STB IMAGE
  "vendor/stb_image/stb_image.h"
  "vendor/stb_image/stb_image.cpp"

 "src/Graphics/Texture.h" "src/Graphics/Texture.cpp" 
 "src/Core/AppazoidSpecification.h"
 "src/ApplicationInterface/Window/WindowHandler.h"
 "src/ApplicationInterface/Window/WindowHandler.cpp"
 "src/ApplicationInterface/Window/WindowStyle.h")

#Appazoid Add Include Directories
target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    #${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/glm # glm is a head-only library so it doesn't need to get linked
    ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
)


target_link_libraries(
    ${PROJECT_NAME}
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
