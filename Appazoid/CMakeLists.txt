# CMakeList.txt : CMake project for Appazoid, include source and define
# project specific logic here.
#

project(Appazoid)

add_library(
${PROJECT_NAME}
STATIC
src/ApplicationInterface/Application.cpp
src/ApplicationInterface/Application.h
include/Appazoid/Appazoid.h
include/Appazoid/UI/widget.h
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
)

#find_package(imgui CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)


#find_package(glfw3 CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

#find_package(glad CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad)
add_subdirectory("vendor")
add_library(appazoid::appazoid ALIAS ${PROJECT_NAME})
