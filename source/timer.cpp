#include <timer.h>
#include <stdio.h>

Timer::Timer()
{
	currentTime = SDL_GetTicks();
	markedTime = currentTime;
	timerOn = false;
}

void Timer::markTimer(Uint32 t)
{
	markedTime = SDL_GetTicks() + t;
	timerOn = true;
}

bool Timer::updateTime()
{
	currentTime = SDL_GetTicks();
	if (timerOn && currentTime >= markedTime)
	{
		timerOn = false;
		return true;
	}
	return false;
}

Uint32 Timer::getCurrentTime()
{
	return currentTime;
}

Uint32 Timer::getMarkedTime()
{
	return markedTime;
}

bool Timer::isTimerOn()
{
	return timerOn;
}

void Timer::setCurrentTime(Uint32 t)
{
	currentTime = t;
}

void Timer::setMarkedTime(Uint32 t)
{
	markedTime = t;
}

void Timer::setTimerState(bool state)
{
	timerOn = state;
}
