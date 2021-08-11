#pragma once
#include <mLine.h>
#include <hitbox.h>
#include <vector>

struct ConeRays
{
	double coneDegrees;
	double coneDirection;
	float range;
	float centreX;
	float centreY;
	int numRays;
	std::vector <mLine> lines;

	ConeRays(float xStart = 0, float yStart = 0, float rayLength = 1, double deg = 0, double dir = 0);
	~ConeRays();

	// Draws the ray of the cones.
	void draw(SDL_Renderer* renderer, Map* map);

	// Move the cone to the coordinates given.
	void move(float x, float y);

	// Change the direction of the cone such that it points to the given coordinates
	void changeDirection(float x, float y);

	// Check if any of the rays collide with the given hitbox.
	// Returns true if there is a collision; false, otherwise.
	bool checkCollision(Hitbox hitbox);

	// Fills in the lines vector according to the data members.
	void fillLines();
};