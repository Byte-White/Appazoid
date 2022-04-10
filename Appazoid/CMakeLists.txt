# CMakeList.txt : CMake project for Appazoid, include source and define
# project specific logic here.
#

project(Appazoid)

add_library(
${PROJECT_NAME}
STATIC
src/ApplicationInterface/Application.cpp
)
target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

add_library(appazoid::appazoid ALIAS ${PROJECT_NAME})

# TODO: Add tests and install targets if needed.
