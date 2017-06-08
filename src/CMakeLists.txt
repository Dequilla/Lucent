# FILE: /src/CMakeLists.txt

# Main Target
add_executable(CEngine Main.cpp)

# Link libraries to the main target
# Release
target_link_libraries(CEngine 
	CEngineCore ${SDL2_LIBRARY} ${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES})

add_subdirectory(Core)