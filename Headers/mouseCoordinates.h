#pragma once

class MouseCoordinates
{
public:
	int x;
	int y;

	MouseCoordinates();

	// Updates x and y using SDL_getMouseState().
	void update();
};