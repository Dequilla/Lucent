#FILE: /CMakeLists.txt
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(CEngine)

# Dependencies directory
set(CEngineDependencies ${PROJECT_SOURCE_DIR}/deps)

# Include dirs
set(ALL_DEP_INCLUDES ${CEngineDependencies}/include)
set(OUR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include our source files
include_directories(${OUR_SRC_DIR})

# Dependencies
if(WIN32)
	# Set SDL2_LIBRARY manually
	set(SDL2_LIBRARY ${CEngineDependencies}/lib/x86/SDL2.lib ${CEngineDependencies}/lib/x86/SDL2main.lib
					 ${CEngineDependencies}/lib/x64/SDL2.lib ${CEngineDependencies}/lib/x64/SDL2main.lib)
	
	# Include our local dependencies for windows
	include_directories(${ALL_DEP_INCLUDES})
elseif(UNIX)
	# Add Module Path
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMAKE)
	
	# Sets SDL2_INCLUDE_DIR and SDL2_LIBRARY
	find_package(SDL2 REQUIRED)

	# Include the found path for SDL2 on UNIX
	include_directories(${SDL2_INCLUDE_DIR})
endif()

add_subdirectory(src)