#pragma once
#include <character.h>
#include <weaponStats.h>

enum playerFrames {
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

class Player : public Character
{
private:
	int gun;
	int melee;
public:
	// Constructors
	Player(int x = 0, int y = 0, int mHealth = 100, int gun = PISTOL, int melee = FISTS);
	// Functions
	// Takes in user input and moves the player character such that it is always moving at a set speed regardless of direction.
	void move(bool* states);
	// Getters
	int getGun();
	int getMelee();
	// Setters
	void setGun(int newGun);
	void setMelee(int newMelee);
};