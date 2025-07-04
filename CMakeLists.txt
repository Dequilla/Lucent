#FILE: /CMakeLists.txt
cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)
project(Lucent)

# Compiler
message("Using compiler ${CMAKE_CXX_COMPILER_ID}")

# Enable c++26
set(CMAKE_CXX_STANDARD 26)

# Export compile_commands.json for LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Dependencies directory
set(LucentDependencies ${PROJECT_SOURCE_DIR}/deps)

# Include dirs
set(ALL_DEP_INCLUDES 	${LucentDependencies}/include/All
						${LucentDependencies}/external)

# Include our source files
set(OUR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OUR_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OUR_SRC_DIR} ${OUR_INC_DIR})

# Dependencies
# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# SDL3 (./script/install_deps.sh has to be run) 
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
include_directories(vendor/SDL/include)

if(WIN32)
	set(WIN_DEP_INCLUDES ${LucentDependencies}/include/Windows)
	
	# Set libraries (TODO: Doesnt seem to work properly always making release being used FIX)
	if(CMAKE_BUILD_TYPE MATCHES DEBUG)
		set(ASSIMP_LIBRARIES ${LucentDependencies}/lib/x86/Debug/assimp-vc140-mt.lib)
		
		set(GLEW_LIBRARIES ${LucentDependencies}/lib/x86/Debug/glew32d.lib)
	
		set(FREETYPE_LIBRARIES ${LucentDependencies}/lib/x86/Debug/freetype28d.lib)
	else()
		set(ASSIMP_LIBRARIES ${LucentDependencies}/lib/x86/Release/assimp-vc140-mt.lib)

		set(GLEW_LIBRARIES ${LucentDependencies}/lib/x86/Release/glew32.lib)

		set(FREETYPE_LIBRARIES ${LucentDependencies}/lib/x86/Release/freetype28.lib)
	endif()

	# Set SDL2_LIBRARY manually
	set(SDL2_LIBRARY ${LucentDependencies}/lib/x86/SDL2.lib ${LucentDependencies}/lib/x86/SDL2main.lib)

	# Include our local dependencies for windows
	include_directories(${ALL_DEP_INCLUDES} ${WIN_DEP_INCLUDES})
elseif(UNIX)
	# Add Module Path
	set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMAKE)
	
	# Sets SDL2_INCLUDE_DIR and SDL2_LIBRARY
	# find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

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
