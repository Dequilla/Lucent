#include "Shader.h"

ce::graphics::Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// Get source
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		std::stringstream vertexStream, fragmentStream;

		// Read file buffers into ss's
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "CE: Failed to read shader file/-s, wrong path?" << std::endl;
	}

	const GLchar* vertexSource = vertexCode.c_str();
	const GLchar* fragmentSource = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// Create, compile, link shaders
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);

	// Check for errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "CE: Failed compiling vertex shader\n Info Log: " << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	// Check for errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "CE: Failed compiling fragment shader\n Info Log: " << infoLog << std::endl;
	}

	// Create and link to program
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertex);
	glAttachShader(this->programID, fragment);
	glLinkProgram(this->programID);

	// Check for errors
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::cout << "CE: Failed linking shader program\n Info Log: " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

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