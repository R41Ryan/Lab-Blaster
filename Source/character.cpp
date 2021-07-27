#include <character.h>
#include <math.h>

Character::Character(int x, int y, int mHealth, int s)
{
	xPos = x;
	yPos = y;
	maxHealth = mHealth;
	currentHealth = mHealth;
	speed = s;
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

void Character::render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip)
{
	SDL_Rect renderClip = { xPos - spriteClip.w/2, yPos - spriteClip.h/2, spriteClip.w, spriteClip.h };

	SDL_RenderCopy(renderer, spriteSheet, &spriteClip, &renderClip);
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

int Character::getSpeed()
{
	return speed;
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

void Character::setSpeed(int s)
{
	speed = s;
}