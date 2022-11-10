# FILE: /src/Graphics/CMakeLists.txt

add_subdirectory(Text)
add_subdirectory(Model)
add_subdirectory(Shader)
add_subdirectory(Renderer)

set(INC_GRAPHICS_DIR ${OUR_INC_DIR}/Graphics)

set(CEngineGraphicsSource 	${INC_GRAPHICS_DIR}/Texture.h	 	Texture.cpp
							${INC_GRAPHICS_DIR}/Lights.h	 	Lights.cpp
							${INC_GRAPHICS_DIR}/Vertex.h
							${INC_GRAPHICS_DIR}/Transform.h 	Transform.cpp

						  ${INC_GRAPHICS_DIR}/Shader/Shader.h			Shader/Shader.cpp
						  ${INC_GRAPHICS_DIR}/Shader/ShaderLoader.h		Shader/ShaderLoader.cpp

						  ${INC_GRAPHICS_DIR}/Text/InitText.h	Text/InitText.cpp
						  ${INC_GRAPHICS_DIR}/Text/Font.h		Text/Font.cpp
						  ${INC_GRAPHICS_DIR}/Text/Text.h		Text/Text.cpp	

						  ${INC_GRAPHICS_DIR}/Renderer/Renderer3D.h			Renderer/Renderer3D.cpp
						  ${INC_GRAPHICS_DIR}/Renderer/ForwardRenderer.h	Renderer/ForwardRenderer.cpp
						  ${INC_GRAPHICS_DIR}/Renderer/RenderCommand.h

						  ${INC_GRAPHICS_DIR}/Model/ModelLoader.h 	Model/ModelLoader.cpp
						  ${INC_GRAPHICS_DIR}/Model/Material.h	  	Model/Material.cpp
						  ${INC_GRAPHICS_DIR}/Model/Mesh.h		  	Model/Mesh.cpp
						  ${INC_GRAPHICS_DIR}/Model/Model.h		  	Model/Model.cpp)


add_library(CEngineGraphics ${CEngineGraphicsSource})