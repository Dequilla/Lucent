# FILE: /src/CMakeLists.txt

# Main Target
add_executable(CEngine Main.cpp)

# Link libraries to the main target
target_link_libraries(CEngine CEngineCore ${SDL2_LIBRARY})

add_subdirectory(Core)