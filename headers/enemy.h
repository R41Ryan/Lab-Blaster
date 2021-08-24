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
	GRUNT_RANGE = 75
};

enum enemyAttackRecovery // Units are in milliseconds
{
	GRUNT_RECOVERY = 500
};

enum enemyState
{
	ENEMY_STATE_NOT_ATTACKING,
	ENEMY_STATE_PREPARE_ATTACK,
	ENEMY_STATE_ATTACKING,
	ENEMY_STATE_ATTACK_RECOVERY
};

class Enemy : public Character
{
private:
	int enemyType;
	int enemyState;

	Timer attackTimer;
public:
	// Constructors

	Enemy(SDL_Renderer* r = NULL, Map* m = NULL, int type = NULL, float x = 0,
		float y = 0, int mHealth = 100, int s = 5, int w = 50, int h = 50);

	// Functions

	// Update the enemyState in regards to attacking the hitbox. 
	// There are three states: not attacking, prepare attack, attacking, and attack recovery.
	// In addition, if the hitbox given is within range of the enemy during the attacking state, returns true. 
	// Otherwise, returns false.
	bool updateAttackState(Hitbox* hitbox);

	// Getters

	int getEnemyType();
	int getEnemyState();
	Timer getAttackTimer();

	// Setters

	void setEnemyType(int type);
	void setEnemyState(int state);
};