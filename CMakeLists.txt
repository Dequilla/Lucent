#FILE: /CMakeLists.txt
cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
project(CEngine)

# Enable c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Dependencies directory
set(CEngineDependencies ${PROJECT_SOURCE_DIR}/deps)

# Include dirs
set(ALL_DEP_INCLUDES ${CEngineDependencies}/include/All)

# Include our source files
set(OUR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OUR_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OUR_SRC_DIR} ${OUR_INC_DIR})

# Dependencies
# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

if(WIN32)
	set(WIN_DEP_INCLUDES ${CEngineDependencies}/include/Windows)
	
	# Set libraries (TODO: Doesnt seem to work properly always making release being used FIX)
	if(CMAKE_BUILD_TYPE MATCHES DEBUG)
		set(ASSIMP_LIBRARIES ${CEngineDependencies}/lib/x86/Debug/assimp-vc140-mt.lib)
		
		set(GLEW_LIBRARIES ${CEngineDependencies}/lib/x86/Debug/glew32d.lib)
	
		set(FREETYPE_LIBRARIES ${CEngineDependencies}/lib/x86/Debug/freetype28d.lib)
	else()
		set(ASSIMP_LIBRARIES ${CEngineDependencies}/lib/x86/Release/assimp-vc140-mt.lib)

		set(GLEW_LIBRARIES ${CEngineDependencies}/lib/x86/Release/glew32.lib)

		set(FREETYPE_LIBRARIES ${CEngineDependencies}/lib/x86/Release/freetype28.lib)
	endif()

	# Set SDL2_LIBRARY manually
	set(SDL2_LIBRARY ${CEngineDependencies}/lib/x86/SDL2.lib ${CEngineDependencies}/lib/x86/SDL2main.lib)

	# Include our local dependencies for windows
	include_directories(${ALL_DEP_INCLUDES} ${WIN_DEP_INCLUDES})
elseif(UNIX)
	# Add Module Path
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMAKE)
	
	# Sets SDL2_INCLUDE_DIR and SDL2_LIBRARY
	find_package(SDL2 REQUIRED)

	# Sets GLEW libraries and includes
	find_package(GLEW REQUIRED)

	# Sets ASSIMP_FOUND, ASSIMP_INCLUDE_DIRS, ASSIMP_LIBRARIES
	find_package(ASSIMP REQUIRED)

	# Find FreeType library
	find_package(Freetype REQUIRED)

	if(ASSIMP_FOUND MATCHES NOT_FOUND)
		message(FATAL_ERROR "Did not find ASSIMP, do you have it installed?")
	elseif(ASSIMP_FOUND MATCHES FOUND)
		message(STATUS "Successfully located assimp!")
	endif()

	# Include the found path for our deps on UNIX
	include_directories(${ASSIMP_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${ALL_DEP_INCLUDES})
endif()

add_subdirectory(src)