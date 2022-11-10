#include "Graphics/Text/Font.h"

ce::graphics::Font::Font()
{
}

ce::graphics::Font::Font(std::string path)
{
	load(path);
}

ce::graphics::Font::~Font()
{
	FT_Done_Face(m_ftFace);
}

bool ce::graphics::Font::load(std::string path)
{
	FT_Error err = FT_New_Face(ce::graphics::ftLib, path.c_str(), 0, &m_ftFace);
	if (err)
	{
		ce::core::log("Failed to load font (" + path + "), FT error: " + std::string(FT_getErrorMessage(err)), ce::core::LOG_ERROR);
		return false;
	}

	return true;
}

ce::graphics::Character ce::graphics::Font::getCharacter(unsigned long charCode, unsigned int height, unsigned int width)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	ce::graphics::Character character;

	FT_Set_Pixel_Sizes(m_ftFace, width, height);

	FT_Error err = FT_Load_Char(m_ftFace, charCode, FT_LOAD_RENDER);
	if (err)
	{
		ce::core::log("Failed to load glyph: " + std::to_string(charCode) + "(" + (char)charCode + "), FT error: " + std::string(FT_getErrorMessage(err)), ce::core::LOG_ERROR);
		return Character();
	}

	glGenTextures(1, &character.textureID);
	glBindTexture(GL_TEXTURE_2D, character.textureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		m_ftFace->glyph->bitmap.width,
		m_ftFace->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		m_ftFace->glyph->bitmap.buffer
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	character.size = glm::ivec2(m_ftFace->glyph->bitmap.width, m_ftFace->glyph->bitmap.rows);
	character.bearing = glm::ivec2(m_ftFace->glyph->bitmap_left, m_ftFace->glyph->bitmap_top);
	character.advance = m_ftFace->glyph->advance.x;

	glBindTexture(GL_TEXTURE_2D, 0);

	return character;
}