# FILE: /src/Core/CMakeLists.txt
set(CEngineCoreSource Window.h Window.cpp
					  Input.h  Input.cpp  
					  Keycodes.h GameMode.h)

add_library(CEngineCore ${CEngineCoreSource})