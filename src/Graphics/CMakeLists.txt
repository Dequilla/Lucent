# FILE: /src/Core/CMakeLists.txt
set(CEngineGraphicsSource Shader.h	   Shader.cpp
						  Camera.h	   Camera.cpp
						  Texture.h	   Texture.cpp
						  Mesh.h	   Mesh.cpp
						  Model.h	   Model.cpp
						  Lights.h	   Lights.cpp
						  Scene.h	   Scene.cpp
						  Renderer3D.h
						  ForwardRenderer.h ForwardRenderer.cpp
						  RenderCommand.h
						  LightSetup.h LightSetup.cpp
						  ShaderManager.h ShaderManager.cpp)


add_library(CEngineGraphics ${CEngineGraphicsSource})