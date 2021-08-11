#pragma once

struct Hitbox
{
	float xPos;
	float yPos;
	int width;
	int height;

	// updates the location of the hitbox according to the given parameters for the position of the object it possesses.
	void update(float x, float y);
};