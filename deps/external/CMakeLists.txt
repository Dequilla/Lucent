#######################3
# ImGUI
set(
    IMGUI_SOURCE

    imgui/imgui.h               imgui/imgui.cpp
    imgui/imconfig.h
    imgui/imgui_internal.h    
                                imgui/imgui_draw.cpp
                                imgui/imgui_tables.cpp
                                imgui/imgui_widgets.cpp
    
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h

    imgui/backends/imgui_impl_opengl3.h   imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_sdl.h       imgui/backends/imgui_impl_sdl.cpp
)

add_library(
    imgui

    ${IMGUI_SOURCE}
)

target_include_directories(
    imgui 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
