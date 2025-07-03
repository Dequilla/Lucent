#include "Graphics/Text/Text.h"

lu::graphics::Text::Text()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(
      GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void
lu::graphics::Text::update()
{
    m_characters.clear();

    for (auto &c : m_text)
    {
        m_characters.push_back(m_font->getCharacter(c, m_size));
    }
}

void
lu::graphics::Text::setFont(Font *font)
{
    m_font = font;

    update();
}

void
lu::graphics::Text::setText(std::string text)
{
    m_text = text;

    update();
}

void
lu::graphics::Text::setSize(unsigned int size)
{
    m_size = size;

    update();
}

void
lu::graphics::Text::setPosition(int x, int y)
{
    m_position = glm::ivec2(x, y);
}

void
lu::graphics::Text::setPosition(glm::ivec2 pos)
{
    m_position = pos;
}

void
lu::graphics::Text::setColor(glm::vec4 color)
{
    m_color = color;
}

void
lu::graphics::Text::setColor(float r, float g, float b, float a)
{
    m_color = glm::vec4(r, g, b, a);
}

void
lu::graphics::Text::draw(lu::graphics::Shader shader)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.use();

    shader.setVec4("textColor", m_color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    GLfloat x = m_position.x;
    GLfloat y = m_position.y;

    glm::vec2 screenSize = lu::core::Application::getScreenBufferSize();
    glm::mat4 projection =
      glm::ortho(0.0f, (float)screenSize.x, 0.0f, (float)screenSize.y);
    shader.setMat4("projection", projection);

    for (auto &c : m_characters)
    {
        GLfloat xpos = x + c.bearing.x;
        GLfloat ypos = y - (c.size.y - c.bearing.y);

        GLfloat w = c.size.x;
        GLfloat h = c.size.y;

        // Screen coordinates and texture coordinates
        GLfloat vertices[6][4] = { { xpos, ypos + h, 0.0, 0.0 },
                                   { xpos, ypos, 0.0, 1.0 },
                                   { xpos + w, ypos, 1.0, 1.0 },

                                   { xpos, ypos + h, 0.0, 0.0 },
                                   { xpos + w, ypos, 1.0, 1.0 },
                                   { xpos + w, ypos + h, 1.0, 0.0 } };

        glBindTexture(GL_TEXTURE_2D, c.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (c.advance >> 6);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}