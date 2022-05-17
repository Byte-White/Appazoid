# CMakeList.txt : CMake project for Appazoid, include source and define
# project specific logic here.
#
project(Sandbox)
# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
"main.cpp"
)

target_link_libraries(
    ${PROJECT_NAME}
    appazoid::appazoid
)


# TODO: Add tests and install targets if needed.
