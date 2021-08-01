#include <mouseCoordinates.h>
#include <SDL.h>

MouseCoordinates::MouseCoordinates()
{
	x = 0;
	y = 0;
}

void MouseCoordinates::update()
{
	SDL_GetMouseState(&x, &y);
}