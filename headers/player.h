#pragma once
#include <character.h>
#include <grunt.h>
#include <weaponStats.h>
#include <myMath.h>

enum playerSprites {
	PLAYER_IDLE,
	PLAYER_TOTAL_SPRITES
};

enum inputKeys {
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	TOTAL_KEYS
};

enum inputMouseButtons {
	LEFT_MOUSE_BUTTON,
	RIGHT_MOUSE_BUTTON,
	TOTAL_MOUSE_BUTTONS
};

class Player : public Character
{
private:
	bool shooting;
	bool meleeing;
	int gun;
	int melee;

	Timer gunTimer;
	Timer meleeTimer;
public:
	// Constructors
	Player(int e = 0, int x = 0, int y = 0, int mHealth = 100, int s = 5, int w = 50, int h = 50, 
		int gun = PISTOL, int melee = FISTS);
	// Functions
	// Takes in user input and moves the player character such that it is always moving at a set speed regardless of direction.
	void move(bool* states, int mapWidth, int mapHeight);
	// Fires the gun that is equipped in the general direction of the mouse.
	void shoot(SDL_Renderer* renderer, int screenWidth, int screenHeight, int mouseX, int mouseY, WeaponStats stats);
	// Renders the character according to the given renderer and clip of the sprite sheet.
	void render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
		int screenWidth, int screenHeight);
	// Returns the distance between the Player's position and another position according to the x and y parameters.
	double distanceTo(int x, int y);
	// Checks if the points specified by the x and y parameters collide with any hitbox belonging to any grunt in the array provided. It returns the grunt's array index if there is a collision. Otherwise returns -1.
	int checkPointCollideGrunt(int x, int y, Grunt gArray[], int arrSize);

	// Getters
	int getGun();
	int getMelee();
	bool isShooting();
	bool isMeleeing();
	Timer getGunTimer();
	Timer getMeleeTimer();

	// Setters
	void setGun(int newGun);
	void setMelee(int newMelee);
	void setShooting(bool s);
	void setMeleeing(bool s);
};