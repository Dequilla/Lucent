# FILE: /src/CMakeLists.txt

# Main Target
add_executable(CEngine Main.cpp)

# Fixes compile problems with std on linux
target_compile_features(CEngine PRIVATE cxx_range_for)

# Link libraries to the main target
target_link_libraries(CEngine 
								CEngineCore CEngineGraphics 
								${SDL2_LIBRARY} ${GLEW_LIBRARIES}
								${OPENGL_LIBRARIES} ${ASSIMP_LIBRARIES})

add_subdirectory(Core)
add_subdirectory(Graphics)