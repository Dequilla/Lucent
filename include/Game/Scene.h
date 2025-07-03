#pragma once

#include <string>

#include "Graphics/Renderer/Renderer3D.h"

#include "Game/GameObject.h"

namespace lu
{
    namespace game
    {

        class Scene
        {
            private:
                RootObject m_rootObject;

            public:
                RootObject *getRootObject();
                GameObject *getGameObjectByName(std::string name);
                GameObject *addGameObject(std::string nameOfParent,
                                          GameObject *object);

                void init();
                void begin();

                void tick(float dt);
                void draw(lu::graphics::Renderer3D *renderer);

                void end();
        };

    }
} // End namespace