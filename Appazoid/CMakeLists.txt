# CMakeList.txt : CMake project for Appazoid, include source and define
# project specific logic here.
#

project(Appazoid)

add_library(
${PROJECT_NAME}
STATIC
  "src/ApplicationInterface/Application.cpp"
  "src/ApplicationInterface/Application.h"

  #opengl stuff
  #"src/OpenGL/IndexBuffer.cpp"
  #"src/OpenGL/Renderer.cpp"
  #"src/OpenGL/Shader.cpp"
  #"src/OpenGL/Texture.cpp"
  #"src/OpenGL/VertexArray.cpp"
  #"src/OpenGL/VertexBuffer.cpp"

  "include/Appazoid/Appazoid.h"
  "include/Appazoid/UI/widget.h"
  "include/Appazoid/UI/Texture.h"
  
 
  "vendor/stb_image/stb_image.h"
  "vendor/stb_image/stb_image.cpp"
  )

#Appazoid Add Include Directories
target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    #${PROJECT_SOURCE_DIR}/vendor/glfw/include
)


target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    imgui::imgui
    PUBLIC
    glfw
    PUBLIC
    glad::glad
    #PUBLIC
    #glm::glm
    PUBLIC 
    stb_image::stb_image
)

#find_package(imgui CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)


#find_package(glfw3 CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

#find_package(glad CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)
add_subdirectory("vendor")
add_library(appazoid::appazoid ALIAS ${PROJECT_NAME})
