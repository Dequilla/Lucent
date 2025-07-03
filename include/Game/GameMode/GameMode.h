#pragma once

#include "SDL2/SDL.h"

#include "Core/Input.h"
#include "Game/Scene.h"

namespace lu
{
    namespace game
    {

        class GameMode
        {
            protected:
                lu::game::Scene m_scene;
                lu::core::Input m_input;

            public:
                void checkInput(const SDL_Event &input);

                virtual void init();
                virtual void begin();
                virtual void tick(float dt);
                virtual void draw() = 0;
                virtual void end();

                void draw(lu::graphics::Renderer3D *renderer);
        };

    }
} // End namespace