# FILE: /src/CMakeLists.txt

# Main Target
add_executable(Lucent Main.cpp)

# Fixes compile problems with std on linux
target_compile_features(Lucent PRIVATE cxx_range_for)

# Link libraries to the main target
target_link_libraries(Lucent 
								LucentGame LucentCore LucentGraphics 
								imgui ${CMAKE_DL_LIBS}
								${SDL2_LIBRARY} ${GLEW_LIBRARIES}
								${OPENGL_LIBRARIES} ${ASSIMP_LIBRARIES}
								${FREETYPE_LIBRARIES})

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Game)