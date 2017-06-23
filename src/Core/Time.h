#pragma once

#include "SDL2/SDL.h"

namespace ce { namespace core {


	struct Time
	{
		int time = 0; // The time in milliseconds
		
		int asMicroseconds()	{ return time * 1000; }
		int asMilliseconds()	{ return time; }
		float asSeconds()		{ return (float)time / 1000.f; }
	};

	class Clock
	{
	private:
		unsigned int m_ticksStarted = 0; // Ms at start
	
	public:
		Clock() {}

		void start();

		Time getPassed(); // Time passed since start

		Time restart(); // Get time passed then restarts
	};


}}