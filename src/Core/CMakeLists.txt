# FILE: /src/Core/CMakeLists.txt

add_subdirectory(Utility)

set(CEngineCoreSource Window.h		Window.cpp
					  Input.h		Input.cpp
					  InputCodes.h	
					  Application.h Application.cpp
					  Time.h		Time.cpp

					  Utility/stringutility.h
					  Utility/log.h
					  Utility/console.h)

add_library(CEngineCore ${CEngineCoreSource})
