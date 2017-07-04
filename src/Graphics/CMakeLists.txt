# FILE: /src/Graphics/CMakeLists.txt

add_subdirectory(Text)
add_subdirectory(Model)
add_subdirectory(Shader)
add_subdirectory(Renderer)

set(CEngineGraphicsSource Texture.h	 Texture.cpp
						  Lights.h	 Lights.cpp
						  Vertex.h
						  Transform.h Transform.cpp

						  Shader/Shader.h			Shader/Shader.cpp
						  Shader/ShaderLoader.h		Shader/ShaderLoader.cpp

						  Text/InitText.h	Text/InitText.cpp
						  Text/Font.h		Text/Font.cpp
						  Text/Text.h		Text/Text.cpp	

						  Renderer/Renderer3D.h			Renderer/Renderer3D.cpp
						  Renderer/ForwardRenderer.h	Renderer/ForwardRenderer.cpp
						  Renderer/RenderCommand.h

						  Model/ModelLoader.h Model/ModelLoader.cpp
						  Model/Material.h	  Model/Material.cpp
						  Model/Mesh.h		  Model/Mesh.cpp
						  Model/Model.h		  Model/Model.cpp)


add_library(CEngineGraphics ${CEngineGraphicsSource})