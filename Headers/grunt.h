#pragma once
#include <enemy.h>

enum gruntSprites {
	GRUNT_IDLE,
	GRUNT_TOTAL_SPRITES
};

class Grunt : public Enemy
{
private:

public:
	using Enemy::Enemy;
};