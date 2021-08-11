#pragma once
#include <SDL_render.h>
#include <hitbox.h>
#include <map.h>

struct mLine
{
	float x1;
	float y1;
	float x2;
	float y2;
	float length;

	mLine(float a = NULL, float b = NULL, float c = NULL, float d = NULL);

	// Draws the line onto the given renderer.
	void draw(SDL_Renderer* renderer, Map* map);

	// Check if the line collides with the given, checking at various points along the line.
	// Where or how many points are checked are calculated based on how many intervals to divide the line into.
	bool checkCollision(Hitbox hitbox);
};