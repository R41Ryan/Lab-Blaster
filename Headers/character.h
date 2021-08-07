#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <map.h>
#include <hitbox.h>
#include <string>
#include <timer.h>
#include <screenDimensions.h>
#include <mouseCoordinates.h>

const int TOTAL_GRUNTS = 5;
const int TOTAL_ENEMIES = TOTAL_GRUNTS;

enum characterTypes {
	PLAYER,
	GRUNT,
	TOTAL_CHARACTER_TYPES
};

class Character
{
private:
	float xPos;
	float yPos;
	int maxHealth;
	int currentHealth;
	int speed;
	bool living;

	Hitbox cHitbox;
public:
	// Constructors
	Character(float x = 0, float y = 0, int mHealth = 0, int s = 5, int w = 50, int h = 50);

	// Functions
	// 
	// Based on the given x and y coordinates, move the character in the direction of the coordinates using its speed as the distance travelled.
	// If the character is already at the desired location, it returns 1. If dead, returns -1. Otherwise, it returns 0.
	int move(float x, float y, Hitbox playerHitbox);
	// Increment the character's health by h points. Negative units are allowed. Health cannot be greater than max or less than 0.
	void incrementHealth(int h);
	// Restores the character's health to maxHealth.
	void restoreHealth();
	// Renders the character according onto the given renderer based clip of the sprite sheet and the x and y positions of the map.
	void render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip, Map* map);
	// Checks whether the character will collide with the given hitbox parameters at the given velocities. 
	// If it will, it adjusts the positions and velocities so that it is merely at the edge of the hitbox. 
	// It returns true if it collided, returns false otherwise.
	bool willCollide(float* xVel, float* yVel, Hitbox hitbox);
	// Updates hitbox position
	void updateHitbox();
	// Draws their hitbox
	void drawHitbox(SDL_Renderer* renderer, Map* map);

	// Getter Functions
	float getX();
	float getY();
	int getMaxHealth();
	int getCurrentHealth();
	bool isAlive();
	int getSpeed();
	Hitbox getHitbox();

	// Setter Functions
	void setX(float x);
	void setY(float y);
	void setMaxHealth(int mHealth);
	void setCurrentHealth(int cHealth);
	void setSpeed(int s);
	void setHitbox(int w, int h);
};