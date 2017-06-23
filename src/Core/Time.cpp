#include "Time.h"

void ce::core::Clock::start()
{
	m_ticksStarted = SDL_GetTicks();
}

ce::core::Time ce::core::Clock::getPassed()
{
	Time time;
	time.time = SDL_GetTicks() - m_ticksStarted; // CurrentTicks - TicksAtStartPoint = AmountOfTimePassed

	return time;
}

ce::core::Time ce::core::Clock::restart()
{
	Time time = getPassed();
	start();

	return time;
}