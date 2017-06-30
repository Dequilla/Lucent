#pragma once

#include "SDL2/SDL.h"

#include "Game/Scene.h"
#include "Core/Input.h"

namespace ce { namespace game {

	class GameMode
	{
	protected:
		ce::game::Scene	m_scene;
		ce::core::Input m_input;

	public:
		void checkInput(const SDL_Event& input);

		virtual void begin();
		virtual void init();
		virtual void tick(float dt);
		virtual void draw() = 0;
		virtual void end();

		void draw(ce::graphics::Renderer3D* renderer);
	};

}} // End namespace