#pragma once
#include <map.h>
#include <character.h>
#include <enemy.h>
#include <weaponStats.h>
#include <myMath.h>
#include <coneRays.h>

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
	int meleeWeapon;

	Timer gunTimer;
	Timer meleeTimer;

	ConeRays meleeCone;
public:
	// Constructors

	Player(WeaponStats stats, float x = 0, float y = 0, int mHealth = 100, int s = 5, int w = 50, int h = 50,
		int gun = PISTOL, int melee = FISTS);

	// Functions

	// Takes in user input and moves the player character such that it is always moving at a set speed regardless of direction.
	void move(bool* states, Map* map, Enemy eArray[]);
	// Fires the gun that is equipped in the general direction of the mouse.
	// It sends out a ray that will check for any collisions with hitboxes every pixel it travels.
	// If it does detect a hitbox collition, it will stop scanning and do the appropriate amount of damage based on the player's gun.
	// Otherwise, it will stop at the edge of the map. It will also draw a line from the player's position to where the ray stops.
	void shoot(SDL_Renderer* renderer, Map* map, ScreenDimensions screen, MouseCoordinates mouse,
		Enemy eArray[], WeaponStats stats);
	// It will scan for any enemies within the player's melee cone.
	// For all enemies that are detected, it will do the appropriate amount of damage while also moving them away from the player according to the player's melee knockback stat.
	void melee(Enemy eArray[], WeaponStats stats);
	// Renders the character according to the given renderer and clip of the sprite sheet.
	void render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
		ScreenDimensions screen, Map* map);
	// Returns the distance between the Player's position and another position according to the x and y parameters.
	double distanceTo(int x, int y);
	// Checks if the points specified by the x and y parameters collide with any hitbox belonging to any grunt in the array provided. It returns the grunt's array index if there is a collision. Otherwise returns -1.
	int checkPointCollide(int x, int y, Enemy eArray[], Map* map);
	// Updates melee cone such that it points to the coordinates given
	void updateCone(MouseCoordinates mouse, Map* map);
	// Draws the melee cone
	void drawCone(SDL_Renderer* renderer, Map* map);

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