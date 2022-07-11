
project(glad)

add_library(
${PROJECT_NAME}
STATIC
src/glad.c)

target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

add_library(glad::glad ALIAS ${PROJECT_NAME})