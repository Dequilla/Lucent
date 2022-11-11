#include "Core/Time.h"

void lu::core::Clock::start()
{
	m_ticksStarted = SDL_GetTicks();
}

lu::core::Time lu::core::Clock::getPassed()
{
	Time time;
	time.time = SDL_GetTicks() - m_ticksStarted; // CurrentTicks - TicksAtStartPoint = AmountOfTimePassed

	return time;
}

lu::core::Time lu::core::Clock::restart()
{
	Time time = getPassed();
	start();

	return time;
}