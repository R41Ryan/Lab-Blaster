#include "..\headers\player.h"

Player::Player(int e, int x, int y, int mHealth, int s, int w, int h, int gun, int melee)
{
	setX(x);
	setY(y);
	setMaxHealth(mHealth);
	setCurrentHealth(mHealth);
	setSpeed(s);
	setHitboxWidth(w);
	setHitboxHeight(h);
	shooting = false;
	meleeing = false;
	this->gun = gun;
	this->melee = melee;

	gunTimer = Timer();

	meleeTimer = Timer();
}

void Player::move(bool* states, Map* map)
{
	if (isAlive())
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

		if (xDir != 0 || yDir != 0)
		{
			// Finding x velocity and y velocity using similar triangles
			double hypotenuse = hypot((double)xDir, (double)yDir);
			double convertingFactor = getSpeed() / hypotenuse;

			double xVel = (double)xDir * convertingFactor;
			double yVel = (double)yDir * convertingFactor;

			int newX = getX() + (int)xVel;
			int newY = getY() + (int)yVel;

			if (newX < 0)
			{
				setX(0);
			}
			else if (newX > map->getWidth())
			{
				setX(map->getWidth());
			}
			else
			{
				setX(newX);
			}

			if (newY < 0)
			{
				setY(0);
			}
			else if (newY > map->getHeight())
			{
				setY(map->getHeight());
			}
			else
			{
				setY(newY);
			}
		}
	}
}

void Player::shoot(SDL_Renderer* renderer, Map* map, ScreenDimensions screen, MouseCoordinates mouse,
	Grunt gArray[], int arrSizes[], WeaponStats stats)
{
	if (isAlive())
	{
		if (gunTimer.isTimerOn())
		{
			gunTimer.updateTime();
		}
		else
		{
			int collidingGrunt = -1;

			if ((mouse.x > 0 && mouse.x < screen.width) && (mouse.y > 0 && mouse.y < screen.height))
			{
				SDL_SetRenderDrawColor(renderer, 215, 215, 0, 0xFF);
				int xDif = mouse.x - map->getX() + getX();
				int yDif = mouse.y - map->getY() + getY();
				printf("%d %d\n", xDif, yDif);
				double hypotenus = hypot((double)xDif, (double)yDif);
				double convertingFactor = 1 / hypotenus;

				float x1, y1, x2, y2, xUnit, yUnit;
				x1 = (float)(map->getX() + getX());
				y1 = (float)(map->getY() + getY());
				x2 = (float)(x1 + xDif * convertingFactor);
				y2 = (float)(y1 + yDif * convertingFactor);
				xUnit = x2 - x1;
				yUnit = y2 - y1;

				while ((x1 >= 0 && x1 <= map->getWidth()) && (y1 >= 0 && y1 <= map->getHeight()))
				{
					SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
					SDL_RenderDrawLineF(renderer, x1 + 1, y1 + 1, x2 + 1, y2 + 1);
					SDL_RenderDrawLineF(renderer, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
					SDL_RenderDrawLineF(renderer, x1 + 1, y1 - 1, x2 + 1, y2 - 1);
					SDL_RenderDrawLineF(renderer, x1 - 1, y1 + 1, x2 - 1, y2 + 1);

					x1 += xUnit;
					x2 += xUnit;
					y1 += yUnit;
					y2 += yUnit;

					collidingGrunt = checkPointCollideGrunt((int)x1, (int)y1, gArray, arrSizes[GRUNT]);
					if (collidingGrunt >= 0)
					{
						printf("HIT!.\n");
						break;
					}
				}
			}

			if (collidingGrunt > 0)
			{
				gArray[collidingGrunt].incrementHealth(-stats.getGunDamage(getGun()));
				printf("Dealing %d points of damage. Remaining health: %d.\n", stats.getGunDamage(getGun()),
					gArray[collidingGrunt].getCurrentHealth());
			}

			Uint32 fireRateMilliseconds = (Uint32)(1000 /
				stats.getGunFireRate(PISTOL));
			gunTimer.markTimer(fireRateMilliseconds);
		}
	}
}

void Player::render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
	ScreenDimensions screen)
{
	if (isAlive())
	{
		SDL_Rect renderClip = { screen.width / 2 - spriteClip.w / 2, screen.height / 2 - spriteClip.h / 2, spriteClip.w, spriteClip.h };

		SDL_RenderCopy(renderer, spriteSheet, &spriteClip, &renderClip);
	}
}

double Player::distanceTo(int x, int y)
{
	double xDif = (double)(x - getX());
	double yDif = (double)(y - getY());
	return hypot(xDif, yDif);
}

int Player::checkPointCollideGrunt(int x, int y, Grunt gArray[], int arrSize)
{
	int closestIndex = -1;
	double smallestDistance = -1.f;
	double currentDistance;
	int currentLeft;
	int currentRight;
	int currentTop;
	int currentBottom;
	for (int i = 0; i < arrSize; i++)
	{
		if (gArray[i].isAlive())
		{
			currentLeft = gArray[i].getX() - gArray[i].getHitboxWidth() / 2;
			currentRight = gArray[i].getX() + gArray[i].getHitboxWidth() / 2;
			currentTop = gArray[i].getY() - gArray[i].getHitboxHeight() / 2;
			currentBottom = gArray[i].getY() + gArray[i].getHitboxHeight() / 2;

			// If the point is in the hitbox
			if ((x >= currentLeft && x <= currentRight) && (y >= currentTop && y <= currentBottom))
			{
				currentDistance = distanceTo(gArray[i].getX(), gArray[i].getY());
				if (closestIndex == -1)
				{
					closestIndex = i;
					smallestDistance = currentDistance;
				}
				else if (currentDistance < smallestDistance)
				{
					closestIndex = i;
					smallestDistance = currentDistance;
				}
			}
		}
	}

	return closestIndex;
}

int Player::getGun()
{
	return gun;
}

int Player::getMelee()
{
	return melee;
}

bool Player::isShooting()
{
	return shooting;
}

bool Player::isMeleeing()
{
	return meleeing;
}

Timer Player::getGunTimer()
{
	return gunTimer;
}

Timer Player::getMeleeTimer()
{
	return meleeTimer;
}

void Player::setGun(int newGun)
{
	gun = newGun;
}

void Player::setMelee(int newMelee)
{
	melee = newMelee;
}

void Player::setShooting(bool s)
{
	shooting = s;
}

void Player::setMeleeing(bool s)
{
	meleeing = s;
}
