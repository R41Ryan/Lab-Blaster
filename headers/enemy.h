#pragma once
#include <character.h>

enum gruntSprites {
	GRUNT_IDLE,
	GRUNT_TOTAL_SPRITES
};

class Enemy : public Character
{
private:

public:
	using Character::Character;
};