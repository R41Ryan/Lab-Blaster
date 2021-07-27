#include "..\headers\player.h"

Player::Player(int x, int y, int mHealth, int gun, int melee)
{
	setX(x);
	setY(y);
	setMaxHealth(mHealth);
	setCurrentHealth(mHealth);
	this->gun = gun;
	this->melee = melee;
}

void Player::move(bool* states)
{
	int xDir = 0;
	int yDir = 0;

	if (states[KEY_W])
	{
		yDir = -1;
	}

	if (states[KEY_S])
	{
		yDir = 1;
	}

	if (states[KEY_A])
	{
		xDir = -1;
	}

	if (states[KEY_D])
	{
		xDir = 1;
	}

	float xVel = 0;
	float yVel = 0;

	if (xDir == 0)
	{
		if (yDir == 1)
		{
			yVel = getSpeed();
		}
		else if (yDir == -1)
		{
			yVel = -getSpeed();
		}
	}
	else
	{
		float angle = atan(yDir / xDir);

		xVel = xDir * getSpeed() * cos(angle);
		yVel = yDir * abs(getSpeed() * sin(angle));
	}

	setX(getX() + xVel);
	setY(getY() + yVel);
}

int Player::getGun()
{
	return gun;
}

int Player::getMelee()
{
	return melee;
}

void Player::setGun(int newGun)
{
	gun = newGun;
}

void Player::setMelee(int newMelee)
{
	melee = newMelee;
}
