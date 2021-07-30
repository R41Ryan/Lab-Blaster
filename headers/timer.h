#pragma once
#include <SDL.h>

class Timer 
{
private:
	Uint32 currentTime;
	Uint32 markedTime;
	bool timerOn;
public:
	// Constructor
	Timer();
	// Functions
	// Sets timerOn to true and sets markedTime to t milliseconds after currentTime.
	void markTimer(Uint32 t);
	// Updates the current time with SDL_GetTicks(). If currentTime becomes greater than or equal to marked time, it returns true and timerSet is set to false. It returns false otherwise.
	bool updateTime();
	// Getter
	Uint32 getCurrentTime();
	Uint32 getMarkedTime();
	bool isTimerOn();

	// Setter
	void setCurrentTime(Uint32 t);
	void setMarkedTime(Uint32 t);
	void setTimerState(bool state);
};