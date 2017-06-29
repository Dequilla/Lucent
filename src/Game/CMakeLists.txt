# FILE: /src/Game/CMakeLists.txt

add_subdirectory(Components)

set(CEngineGameSource    Scene.h		Scene.cpp
						 GameObject.h	GameObject.cpp
						 
						 Components/ComponentIncludes.h
						 Components/BaseComponent.h			Components/BaseComponent.cpp
						 Components/ModelComponent.h		Components/ModelComponent.cpp
						 Components/TransformComponent.h	Components/TransformComponent.cpp)

add_library(CEngineGame ${CEngineGameSource})