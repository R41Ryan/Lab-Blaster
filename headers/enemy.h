#pragma once
#include <character.h>
#include <timer.h>

enum gruntSprites 
{
	GRUNT_IDLE,
	GRUNT_TOTAL_SPRITES
};

enum enemyDamage
{
	GRUNT_DAMAGE = 20
};

enum enemyRange // Units are in pixels
{
	GRUNT_RANGE = 90
};

enum enemyAttackRate // Units are in attacks per second
{
	GRUNT_ATTACK_RATE = 1
};

class Enemy : public Character
{
private:
	int enemyType;

	Timer attackTimer;
public:
	// Constructors

	Enemy(int type = NULL, float x = 0, float y = 0, int mHealth = 100, int s = 5, int w = 50, int h = 50);

	// Functions

	// Returns true if in attack range of hitbox. the distance depends on the current enemyType.
	bool canAttack(Hitbox* hitbox);

	// Getters

	int getEnemyType();

	// Setters

	void setEnemyType(int type);
};