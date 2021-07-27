#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <string>

enum characterTypes {
	PLAYER,
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
	// Change the xPos by x units, and the yPos by y units.
	void move(int x, int y);
	// Increment the character's health by h points. Negative units are allowed. Health cannot be greater than max or less than 0.
	void incrementHealth(int h);
	// Restores the character's health to maxHealth.
	void restoreHealth();
	// Renders the character according to the given renderer and clip of the sprite sheet.
	void render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip);

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