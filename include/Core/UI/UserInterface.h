#pragma once
#include <SDL.h>
#include <SDL_opengl.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace lu { namespace core { namespace ui {

    inline bool initUserInterfaceComponents(SDL_Window* sdlWindow, SDL_GLContext glContext)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(sdlWindow, glContext);
        ImGui_ImplOpenGL3_Init("#version 130");

        return false;
    }

    inline void processEvents(const SDL_Event* event)
    {
        ImGui_ImplSDL2_ProcessEvent(event);
    }

    inline void createFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

}}}