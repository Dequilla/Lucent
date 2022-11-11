# FILE: /src/Game/CMakeLists.txt

add_subdirectory(Components)
add_subdirectory(GameMode)
add_subdirectory(GameObjects)

set(INC_GAME_DIR ${OUR_INC_DIR}/Game)

set(LucentGameSource   ${INC_GAME_DIR}/Scene.h							Scene.cpp
						 	
						${INC_GAME_DIR}/GameObject.h					GameObject.cpp
						${INC_GAME_DIR}/GameObjects/CameraObject.h 		GameObjects/CameraObject.cpp
						${INC_GAME_DIR}/GameObjects/ModelObject.h		GameObjects/ModelObject.cpp
						${INC_GAME_DIR}/GameObjects/LightObjects.h		GameObjects/LightObjects.cpp
	
						${INC_GAME_DIR}/GameMode/GameMode.h				GameMode/GameMode.cpp
						${INC_GAME_DIR}/GameMode/ExampleGameMode.h 		GameMode/ExampleGameMode.cpp

						${INC_GAME_DIR}/Components/BaseComponent.h		Components/BaseComponent.cpp
						${INC_GAME_DIR}/Components/ModelComponent.h		Components/ModelComponent.cpp
						${INC_GAME_DIR}/Components/CameraComponent.h	Components/CameraComponent.cpp
						${INC_GAME_DIR}/Components/TransformComponent.h	Components/TransformComponent.cpp
						${INC_GAME_DIR}/Components/LightComponents.h	Components/LightComponents.cpp)

add_library(LucentGame ${LucentGameSource})