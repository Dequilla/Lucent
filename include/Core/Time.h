/**
* \file Time.h
*/
#pragma once

#include "SDL2/SDL.h"

namespace ce { namespace core {

	/**
	* \brief Represents time in diffrent formats
	* 
	* Internally uses milliseconds and easily transfers it to other formats for use in the engine.
	*/
	struct Time
	{
		int time = 0;  /**<  The time in milliseconds */
		
		int asMicroseconds()	{ return time * 1000; }
		int asMilliseconds()	{ return time; }
		float asSeconds()		{ return (float)time / 1000.f; }
	};


	/**
	* \brief A simple clock
	*/
	class Clock
	{
	private:
		unsigned int m_ticksStarted = 0; // Milliseconds at start
	
	public:
		Clock() {}

		void start(); /**< Start clock */

		Time getPassed(); /**< Get the Time passed since start or restart */

		Time restart(); /**< Get Time passed then restart the clock */
	};


}}