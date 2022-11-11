# FILE: /src/Core/CMakeLists.txt

add_subdirectory(Utility)

set(INC_CORE_DIR ${OUR_INC_DIR}/Core)

set(LucentCoreSource 	${INC_CORE_DIR}/Window.h		Window.cpp
						${INC_CORE_DIR}/Input.h			Input.cpp
						${INC_CORE_DIR}/InputCodes.h	
						${INC_CORE_DIR}/Application.h 	Application.cpp
						${INC_CORE_DIR}/Time.h			Time.cpp

						${INC_CORE_DIR}/Utility/stringutility.h
						${INC_CORE_DIR}/Utility/log.h
						${INC_CORE_DIR}/Utility/console.h)

add_library(LucentCore ${LucentCoreSource})
