#include <character.h>

Character::Character(int x, int y, int mHealth)
{
	xPos = x;
	yPos = y;
	maxHealth = mHealth;
	currentHealth = mHealth;
	living = true;
}

void Character::move(int x, int y)
{
	xPos += x;
	yPos += y;
}

void Character::incrementHealth(int h)
{
	if (currentHealth + h > maxHealth)
	{
		currentHealth = maxHealth;
	}
	else if (currentHealth + h < 0)
	{
		currentHealth = 0;
		living = false;
	}
	else
	{
		currentHealth += h;
	}
}

void Character::restoreHealth()
{
	currentHealth = maxHealth;
}

int Character::getX()
{
	return xPos;
}

int Character::getY()
{
	return yPos;
}

int Character::getMaxHealth()
{
	return maxHealth;
}

int Character::getCurrentHealth()
{
	return currentHealth;
}

bool Character::isAlive()
{
	return living;
}

void Character::setX(int x)
{
	xPos = x;
}

void Character::setY(int y)
{
	yPos = y;
}

void Character::setMaxHealth(int h)
{
	maxHealth = h;
}

void Character::setCurrentHealth(int h)
{
	currentHealth = h;
}