# FILE: /src/Graphics/CMakeLists.txt

add_subdirectory(Model)
add_subdirectory(Shader)
add_subdirectory(Renderer)

set(CEngineGraphicsSource Camera.h	 Camera.cpp
						  Texture.h	 Texture.cpp
						  Lights.h	 Lights.cpp
						  Vertex.h

						  Shader/Shader.h			Shader/Shader.cpp
						  Shader/ShaderLoader.h		Shader/ShaderLoader.cpp

						  Renderer/Renderer3D.h			Renderer/Renderer3D.cpp
						  Renderer/ForwardRenderer.h	Renderer/ForwardRenderer.cpp
						  Renderer/RenderCommand.h

						  Model/ModelLoader.h Model/ModelLoader.cpp
						  Model/Material.h	  Model/Material.cpp
						  Model/Mesh.h		  Model/Mesh.cpp
						  Model/Model.h		  Model/Model.cpp)


add_library(CEngineGraphics ${CEngineGraphicsSource})