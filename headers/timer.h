#pragma once
#include <SDL.h>

class Timer 
{
private:
	Uint32 time;
public:
	// Constructor
	Timer();
	// Functions

	// Getter
	Uint32 getTime();

	// Setter
	void setTime(Uint32 t);
};