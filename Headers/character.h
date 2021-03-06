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

const int TOTAL_GRUNTS = 1;
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

	Map* map;
	SDL_Renderer* renderer;
public:
	// Constructors

	Character(SDL_Renderer* r = NULL, Map* m = NULL, float x = 0, float y = 0, int mHealth = 0, int s = 5, int w = 50, int h = 50);

	// Functions
	
	// Based on the given x and y coordinates, move the character in the direction of the coordinates using its speed as the distance travelled.
	// If the character is already at the desired location, it returns 1. If dead, returns -1. Otherwise, it returns 0.
	// The hitboxes are to avoid collisions with entities.
	int moveTo(float x, float y, float distance, Hitbox* playerHitbox, Hitbox* enemyHitboxes[]);
	// Moves the player away from a point given by the x and y coordinates by distance pixels. 
	// The hitboxes are to avoid collisions with entities.
	void moveFrom(float x, float y, float distance, Hitbox* playerHitbox, Hitbox* enemyHitboxes[]);
	// Teleports the character to the given coordinates on the given map with full health. 
	// If no coordinates are inputted, it teleports to a random location on the given map.
	void spawn(float x = NULL, float y = NULL);
	// Increment the character's health by h points. Negative units are allowed. Health cannot be greater than max or less than 0.
	void incrementHealth(int h);
	// Restores the character's health to maxHealth.
	void restoreHealth();
	// Returns the distance between the character's position and another position according to the x and y parameters.
	float distanceTo(int x, int y);
	// Renders the character according onto the given renderer based clip of the sprite sheet and the x and y positions of the map.
	void render(SDL_Texture* spriteSheet, SDL_Rect spriteClip);
	// Checks whether the character will collide with the given hitbox parameters at the given velocities. 
	// If it will, it adjusts the positions and velocities so that it is merely at the edge of the hitboxes. 
	// It returns true if it collided, returns false otherwise.
	bool willCollide(float* xVel, float* yVel, Hitbox* hitbox);
	// Updates hitbox position
	void updateHitbox();
	// Draws their hitbox
	void drawHitbox();

	// Getter Functions

	float getX();
	float getY();
	int getMaxHealth();
	int getCurrentHealth();
	bool isAlive();
	int getSpeed();
	Hitbox* getHitbox();
	SDL_Renderer* getRenderer();
	Map* getMap();

	// Setter Functions

	void setX(float x);
	void setY(float y);
	void setMaxHealth(int mHealth);
	void setCurrentHealth(int cHealth);
	void setSpeed(int s);
	void setLiving(bool state);
	void setHitbox(int w, int h);
	void setRenderer(SDL_Renderer* r);
	void setMap(Map* m);
};