# FILE: /src/Core/CMakeLists.txt
set(CEngineCoreSource Window.h		Window.cpp
					  Input.h		Input.cpp
					  Application.h Application.cpp
					  InputCodes.h	GameMode.h
					  Time.h		Time.cpp)

add_library(CEngineCore ${CEngineCoreSource})