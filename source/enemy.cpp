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

	enemyState = ENEMY_STATE_NOT_ATTACKING;

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
		float centreX, centreY;
		switch (enemyState)
		{
		case ENEMY_STATE_NOT_ATTACKING:
			centreX = hitbox->xPos + hitbox->width / 2;
			centreY = hitbox->yPos + hitbox->height / 2;
			switch (enemyType)
			{
			case GRUNT:
				if (distanceTo(centreX, centreY) <= (float)GRUNT_RANGE)
				{
					enemyState = ENEMY_STATE_PREPARE_ATTACK;
					attackTimer.markTimer(250);
				}
				break;
			}
			break;
		case ENEMY_STATE_PREPARE_ATTACK:
			enemyState = ENEMY_STATE_ATTACKING;
			break;
		case ENEMY_STATE_ATTACKING:
			ableToAttack = true;
			enemyState = ENEMY_STATE_ATTACK_RECOVERY;
			switch (enemyType)
			{
			case GRUNT:
				attackTimer.markTimer(1000 / GRUNT_ATTACK_RATE);
				break;
			}
			break;
		case ENEMY_STATE_ATTACK_RECOVERY:
			enemyState = ENEMY_STATE_NOT_ATTACKING;
			break;
		}
	}
	return ableToAttack;
}

int Enemy::getEnemyType()
{
	return enemyType;
}

int Enemy::getEnemyState()
{
	return enemyState;
}

Timer Enemy::getAttackTimer()
{
	return attackTimer;
}

void Enemy::setEnemyType(int type)
{
	enemyType = type;
}

void Enemy::setEnemyState(int state)
{
	enemyState = state;
}
