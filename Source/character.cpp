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

int Character::move(int x, int y)
{
	int xDif = x - xPos;
	int yDif = y - yPos;

	if (xDif + yDif == 0)
	{
		return 1;
	}

	// Using similar triangles to determing xVel and yVel.
	double hypotenuse = hypot((double)xDif, (double)yDif);
	double convertingFactor = speed / hypotenuse;

	xPos += (int)(xDif * convertingFactor);
	yPos += (int)(yDif * convertingFactor);

	return 0;
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

void Character::render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
	int mapXPos, int mapYPos)
{
	int renderXPos = mapXPos + xPos;
	int renderYPos = mapYPos + yPos;

	SDL_Rect renderClip = { renderXPos - spriteClip.w/2, renderYPos - spriteClip.h/2, spriteClip.w, spriteClip.h };

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