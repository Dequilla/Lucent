#include "ShaderLoader.h"

// Define static member
std::vector<std::pair<ce::graphics::ShaderProperties, ce::graphics::Shader>> ce::graphics::ShaderLoader::m_loadedShaders;

ce::graphics::Shader ce::graphics::ShaderLoader::loadFromSource(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource)
{
	unsigned int vertex, fragment, programID;
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
		ce::core::log("Failed compiling vertex shader\n Info Log: " + std::string(infoLog), ce::core::LOG_ERROR);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	// Check for errors
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		ce::core::log("Failed compiling fragment shader\n Info Log : " + std::string(infoLog), ce::core::LOG_ERROR);
	}

	// Create and link to program
	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	// Check for errors
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		ce::core::log("Failed linking shader program\n Info Log : " + std::string(infoLog), ce::core::LOG_ERROR);
	}

	Shader shader;
	shader.programID = programID;

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return shader;
}

ce::graphics::Shader ce::graphics::ShaderLoader::loadShader(ShaderProperties properties)
{
	// If it doesn't exist, load it
	if(!alreadyExists(properties))
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
			vertexFile.open(properties.vPath);
			fragmentFile.open(properties.fPath);

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
			ce::core::log("Failed to read shader-file / -s, wrong path? \
					\n-- Path vertex: " + properties.vPath
				+ " \n-- Path fragment: " + properties.fPath 
				+ " \n-- Path geometry: " + properties.gPath
				, ce::core::LOG_WARNING);
		}

		// Set the maximum amount of lights
		fragmentCode = core::string::replace(fragmentCode, "${NUM_DIR_LIGHTS}", std::to_string(ce::core::Application::getInstance().maxDirLights));

		// Comment out lightingloop if we have no lights
		fragmentCode = core::string::replace(fragmentCode, "${HAS_DIR_LIGHT1}", (ce::core::Application::getInstance().maxDirLights > 0) ? "" : "//");
		fragmentCode = core::string::replace(fragmentCode, "${HAS_DIR_LIGHT2}", (ce::core::Application::getInstance().maxDirLights > 0) ? "" : "//");

		fragmentCode = core::string::replace(fragmentCode, "${NUM_POINT_LIGHTS}", std::to_string(ce::core::Application::getInstance().maxPointLights));
		// Comment out lightingloop if we have no lights
		fragmentCode = core::string::replace(fragmentCode, "${HAS_POINT_LIGHT1}", (ce::core::Application::getInstance().maxPointLights > 0) ? "" : "//");
		fragmentCode = core::string::replace(fragmentCode, "${HAS_POINT_LIGHT2}", (ce::core::Application::getInstance().maxPointLights > 0) ? "" : "//");

		fragmentCode = core::string::replace(fragmentCode, "${NUM_SPOT_LIGHTS}", std::to_string(ce::core::Application::getInstance().maxSpotLights));
		// Comment out lightingloop if we have no lights
		fragmentCode = core::string::replace(fragmentCode, "${HAS_SPOT_LIGHT1}", (ce::core::Application::getInstance().maxSpotLights > 0) ? "" : "//");
		fragmentCode = core::string::replace(fragmentCode, "${HAS_SPOT_LIGHT2}", (ce::core::Application::getInstance().maxSpotLights > 0) ? "" : "//");

		const GLchar* vertexSource = vertexCode.c_str();
		const GLchar* fragmentSource = fragmentCode.c_str();

		m_loadedShaders.emplace_back(std::make_pair(properties, loadFromSource(vertexSource, fragmentSource)));
	}

	// When loaded or if it already existed return pointer to it
	for (auto &shader : m_loadedShaders)
	{
		if (shader.first == properties)
		{
			return shader.second;
		}
	}
}

bool ce::graphics::ShaderLoader::alreadyExists(ShaderProperties properties)
{
	for (auto &shader : m_loadedShaders)
	{
		if( shader.first == properties )
		{
			return true;
		}
	}
	return false;
}