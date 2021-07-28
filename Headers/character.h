#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <string>

enum characterTypes {
	PLAYER,
	GRUNT,
	TOTAL_CHARACTER_TYPES
};

class Character
{
private:
	int xPos;
	int yPos;
	int maxHealth;
	int currentHealth;
	int speed;
	bool living;

public:
	// Constructors
	Character(int x = 0, int y = 0, int mHealth = 0, int s = 5);

	// Functions
	// Based on the given x and y coordinates, move the character in the direction of the coordinates using its speed as the distance travelled.
	// If the character is already at the desired location, it returns 1. Otherwise, it returns 0.
	int move(int x, int y);
	// Increment the character's health by h points. Negative units are allowed. Health cannot be greater than max or less than 0.
	void incrementHealth(int h);
	// Restores the character's health to maxHealth.
	void restoreHealth();
	// Renders the character according onto the given renderer based clip of the sprite sheet and the x and y positions of the map.
	void render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip, int mapWidth, int mapHeight);

	// Getter Functions
	int getX();
	int getY();
	int getMaxHealth();
	int getCurrentHealth();
	bool isAlive();
	int getSpeed();

	// Setter Functions
	void setX(int x);
	void setY(int y);
	void setMaxHealth(int mHealth);
	void setCurrentHealth(int cHealth);
	void setSpeed(int s);
};