#pragma once

#include "Core/Application.h"

#include "Graphics/Shader/Shader.h"
#include "Graphics/Text/Font.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include <vector>

namespace lu
{
    namespace graphics
    {

        /**
         * \brief A renderable piece of text
         */
        class Text
        {
            protected:
                lu::graphics::Font *m_font;
                std::string m_text = "";
                unsigned int m_size = 48;
                glm::ivec2 m_position;
                glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                std::vector<lu::graphics::Character> m_characters;

                GLuint m_VAO, m_VBO;

                void update(); /**< Updates the characters */

            public:
                Text();

                void setFont(Font *font);
                void setText(std::string text);
                void setSize(unsigned int size);
                void setPosition(int x, int y);
                void setPosition(glm::ivec2 pos);
                void setColor(glm::vec4 color);
                void setColor(float r, float g, float b, float a = 1.0f);

                void draw(lu::graphics::Shader shader);

                std::string getText() { return m_text; }
        };

    }
}