#include "..\headers\enemy.h"

Enemy::Enemy(int type, float x, float y, int mHealth, int s, int w, int h)
{
	if (type == 0)
	{
		enemyType = GRUNT;
	}
	else
	{
		enemyType = type;
	}
	setX(x);
	setY(y);
	setMaxHealth(mHealth);
	setCurrentHealth(mHealth);
	setSpeed(s);

	if (mHealth > 0)
	{
		setLiving(true);
	}
	else
	{
		setLiving(false);
	}

	setHitbox(w, h);
	getHitbox()->active = isAlive();

	attackTimer = Timer();
}

bool Enemy::canAttack(Hitbox* hitbox)
{
	bool ableToAttack = false;;
	if (attackTimer.isTimerOn())
	{
		attackTimer.updateTime();
	}
	else
	{
		float centreX = hitbox->xPos + hitbox->width / 2;
		float centreY = hitbox->yPos + hitbox->height / 2;
		switch (enemyType)
		{
		case GRUNT:
			if (distanceTo(centreX, centreY) <= (float)GRUNT_RANGE)
			{
				attackTimer.markTimer(1000 / GRUNT_ATTACK_RATE);
				ableToAttack = true;
			}
			break;
		}
	}
	return ableToAttack;
}

int Enemy::getEnemyType()
{
	return enemyType;
}

void Enemy::setEnemyType(int type)
{
	enemyType = type;
}
