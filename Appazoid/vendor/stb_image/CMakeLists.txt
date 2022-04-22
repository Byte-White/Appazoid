
project(stb_image)

add_library(
${PROJECT_NAME}
STATIC
stb_image.cpp
stb_image.h
)

target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}
)

add_library(stb_image::stb_image ALIAS ${PROJECT_NAME})