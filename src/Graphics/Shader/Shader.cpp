#include "Shader.h"

void ce::graphics::Shader::use()
{
	glUseProgram(this->programID);
}

void ce::graphics::Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (int)value);
}

void ce::graphics::Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);
}

void ce::graphics::Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);
}

void ce::graphics::Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(this->programID, name.c_str()), 1, &value[0]);
}

void ce::graphics::Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(this->programID, name.c_str()), x, y);
}

void ce::graphics::Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, &value[0]);
}

void ce::graphics::Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->programID, name.c_str()), x, y, z);
}

void ce::graphics::Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(this->programID, name.c_str()), 1, &value[0]);
}

void ce::graphics::Shader::setVec4(const std::string & name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(this->programID, name.c_str()), x, y, z, w);
}

void ce::graphics::Shader::setMat2(const std::string &name, const glm::mat2 &value) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ce::graphics::Shader::setMat3(const std::string &name, const glm::mat3 &value) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ce::graphics::Shader::setMat4(const std::string &name, const glm::mat4 &value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}