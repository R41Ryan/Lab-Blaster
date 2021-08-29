#pragma once
#include "../headers/hitbox.h"
#include <SDL_render.h>
#include "../headers/map.h"

class Interactive
{
private:
	float xPos;
	float yPos;
	Hitbox iHitbox;

	SDL_Renderer* renderer;
	Map* map;

public:
	// Constructors

	Interactive(float x = 0, float y = 0, float w = 0, float h = 0, SDL_Renderer* r = NULL, Map* m = NULL);

	// Functions

	// Displays the hitbox of the interactive object.
	void displayHitbox();

	// Renders the object using the given texture;
	void render(SDL_Texture* texture, SDL_Rect sourceClip);

	// Returns true of the given hitbox is colliding with the hitbox of the interactive. Returns false otherwise.
	bool isColliding(Hitbox* targetHitbox);

	// Getters

	float getX();
	float getY();
	Hitbox* getIHitbox();

	// Setters

	void setX(float x);
	void setY(float y);
	void setIHitbox(float w, float h);
	void setRenderer(SDL_Renderer* r);
	void setMap(Map* m);

};