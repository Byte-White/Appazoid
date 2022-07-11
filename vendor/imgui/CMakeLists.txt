project(ImGui)

add_library(
${PROJECT_NAME}
STATIC
#src
"imconfig.h"
"imgui.h"
"imgui.cpp"
"imgui_draw.cpp"
"imgui_internal.h"
"imgui_tables.cpp"
"imgui_widgets.cpp"
"imstb_rectpack.h"
"imstb_textedit.h"
"imstb_truetype.h"
"imgui_demo.cpp"
#backends
#"backends/imgui_impl_opengl3.h"
#"backends/imgui_impl_opengl3.cpp"
#"backends/imgui_impl_glfw.h"
#"backends/imgui_impl_glfw.cpp"
)

target_include_directories( 
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../glfw/include
)



add_library(imgui::imgui ALIAS ${PROJECT_NAME})
