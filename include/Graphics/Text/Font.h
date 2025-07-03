#pragma once

#include <string>

#include "ft2build.h"
#include FT_FREETYPE_H

#include "Core/Utility/log.h"
#include "InitText.h"

#include "GL/glew.h"
#include "GLM/glm.hpp"

namespace lu
{
    namespace graphics
    {

        struct Character
        {
                GLuint textureID; /**< OpenGL texture id */
                glm::ivec2 size;  /**< Size of the glyph */
                glm::ivec2
                  bearing; /**< Offset from baseline to top/left of glyph */
                GLuint advance; /**< Offset to next glyph */
        };

        class Font
        {
            protected:
                FT_Face m_ftFace;

            public:
                Font();
                Font(std::string path);
                ~Font();

                bool load(std::string path);

                /**
                 * \brief Retrieve a character from the font
                 *
                 * @param charCode the code of the character we wish to retrieve
                 * @param height the height of the character
                 * @param width the width of the character, 0 for dynamic
                 */
                Character getCharacter(unsigned long charCode,
                                       unsigned int height = 48,
                                       unsigned int width = 0);
        };

    }
}