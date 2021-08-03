#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <map.h>
#include <string>
#include <timer.h>
#include <screenDimensions.h>
#include <mouseCoordinates.h>

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

	int hitboxWidth;
	int hitboxHeight;
public:
	// Constructors
	Character(float x = 0, float y = 0, int mHealth = 0, int s = 5, int w = 50, int h = 50);

	// Functions
	// Based on the given x and y coordinates, move the character in the direction of the coordinates using its speed as the distance travelled.
	// If the character is already at the desired location, it returns 1. If dead, returns -1. Otherwise, it returns 0.
	int move(float x, float y);
	// Increment the character's health by h points. Negative units are allowed. Health cannot be greater than max or less than 0.
	void incrementHealth(int h);
	// Restores the character's health to maxHealth.
	void restoreHealth();
	// Renders the character according onto the given renderer based clip of the sprite sheet and the x and y positions of the map.
	void render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip, Map* map);

	// Getter Functions
	float getX();
	float getY();
	int getMaxHealth();
	int getCurrentHealth();
	bool isAlive();
	int getSpeed();
	int getHitboxWidth();
	int getHitboxHeight();

	// Setter Functions
	void setX(float x);
	void setY(float y);
	void setMaxHealth(int mHealth);
	void setCurrentHealth(int cHealth);
	void setSpeed(int s);
	void setHitboxWidth(int w);
	void setHitboxHeight(int h);
};