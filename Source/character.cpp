#include <character.h>
#include <math.h>

Character::Character(float x, float y, int mHealth, int s, int w, int h)
{
	xPos = x;
	yPos = y;
	maxHealth = mHealth;
	currentHealth = mHealth;
	speed = s;
	living = true;
	
	cHitbox.xPos = (float)(x - w / 2);
	cHitbox.yPos = (float)(y - h / 2);
	cHitbox.width = w;
	cHitbox.height = h;
	cHitbox.active = living;
}

int Character::move(float x, float y, Hitbox* playerHitbox, Hitbox* enemyHitboxes[])
{
	if (living)
	{
		float xDif = x - xPos;
		float yDif = y - yPos;

		if (xDif + yDif == 0)
		{
			return 1;
		}

		// Using similar triangles to determing xVel and yVel.
		double hypotenuse = hypot((double)xDif, (double)yDif);
		double convertingFactor = speed / hypotenuse;

		float xVel = (float)(xDif * convertingFactor);
		float yVel = (float)(yDif * convertingFactor);

		willCollide(&xVel, &yVel, playerHitbox);
		for (int i = 0; i < TOTAL_ENEMIES; i++)
		{
			willCollide(&xVel, &yVel, enemyHitboxes[i]);
			// printf("%f, %f\n", xVel, yVel);
		}
		

		xPos += xVel;
		yPos += yVel;

		cHitbox.update(xPos, yPos);

		return 0;
	}
	return -1;
}

void Character::incrementHealth(int h)
{
	if (currentHealth + h > maxHealth)
	{
		currentHealth = maxHealth;
	}
	else if (currentHealth + h <= 0)
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
	living = true;
}

void Character::render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
	Map* map)
{
	if (living)
	{
		int renderXPos = (int)(map->getX() + xPos);
		int renderYPos = (int)(map->getY() + yPos);

		SDL_Rect renderClip = { renderXPos - spriteClip.w / 2, renderYPos - spriteClip.h / 2, spriteClip.w, spriteClip.h };

		SDL_RenderCopy(renderer, spriteSheet, &spriteClip, &renderClip);
	}
}

bool Character::willCollide(float* xVel, float* yVel, Hitbox* hitbox)
{
	if (hitbox == &cHitbox || !hitbox->active)
	{
		printf("%d\n", hitbox->active);
		return false;
	}

	bool isLeft = cHitbox.xPos + cHitbox.width <= hitbox->xPos;
	bool isRight = cHitbox.xPos >= hitbox->xPos + hitbox->width;
	bool isAbove = cHitbox.yPos + cHitbox.height <= hitbox->yPos;
	bool isBelow = cHitbox.yPos >= hitbox->yPos + hitbox->height;
	bool collided = false;

	if ((!isLeft && !isRight) && (!isAbove && !isBelow))
	{
		printf("Colliding hitboxes.\n");
		// This means the hitbox is already within the target hitbox.
		collided = true;

		float distanceToSides[4]; // 0 = left, 1 = top, 2 = right, 3 = bottom.
		distanceToSides[0] = abs(xPos - hitbox->xPos);
		distanceToSides[1] = abs(yPos - hitbox->yPos);
		distanceToSides[2] = abs(xPos - hitbox->xPos - hitbox->width);
		distanceToSides[3] = abs(yPos - hitbox->yPos - hitbox->height);

		int closestSide = 0;
		float smallestDistance = distanceToSides[closestSide];
		for (int i = 0; i < 4; i++)
		{
			if (distanceToSides[i] < smallestDistance)
			{
				closestSide = i;
				smallestDistance = distanceToSides[closestSide];
			}
		}

		switch (closestSide)
		{
		case 0:
			xPos = hitbox->xPos - cHitbox.width / 2;
			*xVel = 0;
			break;
		case 1:
			yPos = hitbox->yPos - cHitbox.height / 2;
			*yVel = 0;
			break;
		case 2:
			xPos = hitbox->xPos + hitbox->width + cHitbox.width / 2;
			*xVel = 0;
			break;
		case 3:
			yPos = hitbox->yPos + hitbox->height + cHitbox.height / 2;
			*yVel = 0;
			break;
		}
	}
	else
	{
		if ((isLeft && cHitbox.xPos + cHitbox.width + *xVel > hitbox->xPos) && !(isAbove || isBelow))
		{
			// printf("Hits left side.\n");
			xPos = hitbox->xPos - cHitbox.width / 2;
			*xVel = 0;
			collided = true;
		}

		if ((isRight && cHitbox.xPos + *xVel < hitbox->xPos + hitbox->width) && !(isAbove || isBelow))
		{
			// printf("Hits right side.\n");
			xPos = hitbox->xPos + hitbox->width + cHitbox.width / 2;
			*xVel = 0;
			collided = true;
		}

		if ((isAbove && cHitbox.yPos + cHitbox.height + *yVel > hitbox->yPos) && !(isLeft || isRight))
		{
			// printf("Hits top side.\n");
			yPos = hitbox->yPos - cHitbox.height / 2;
			*yVel = 0;
			collided = true;
		}

		if ((isBelow && cHitbox.yPos + *yVel < hitbox->yPos + hitbox->height) && !(isLeft || isRight))
		{
			// printf("Hits top side.\n");
			yPos = hitbox->yPos + hitbox->height + cHitbox.height / 2;
			*yVel = 0;
			collided = true;
		}
	}

	cHitbox.update(xPos, yPos);

	return collided;
}

void Character::updateHitbox()
{
	cHitbox.update(xPos, yPos);
}

void Character::drawHitbox(SDL_Renderer* renderer, Map* map)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	SDL_Rect renderRect = { map->getX() + cHitbox.xPos, map->getY() + cHitbox.yPos, cHitbox.width, cHitbox.height };
	SDL_RenderDrawRect(renderer, &renderRect);
}

float Character::getX()
{
	return xPos;
}

float Character::getY()
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

Hitbox* Character::getHitbox()
{
	return &cHitbox;
}

void Character::setX(float x)
{
	xPos = x;
}

void Character::setY(float y)
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

void Character::setHitbox(int w, int h)
{
	cHitbox.xPos = this->xPos - w / 2;
	cHitbox.yPos = this->yPos - h / 2;
	cHitbox.width = w;
	cHitbox.height = h;
}