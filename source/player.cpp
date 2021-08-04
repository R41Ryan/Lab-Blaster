#include "..\headers\player.h"

Player::Player(int e, float x, float y, int mHealth, int s, int w, int h, int gun, int melee)
{
	setX(x);
	setY(y);
	setMaxHealth(mHealth);
	setCurrentHealth(mHealth);
	setSpeed(s);
	setHitbox(w, h);
	shooting = false;
	meleeing = false;
	this->gun = gun;
	this->melee = melee;

	gunTimer = Timer();

	meleeTimer = Timer();
}

void Player::move(bool* states, Map* map, Enemy eArray[])
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
			float hypotenuse = hypotf((float)xDir, (float)yDir);
			float convertingFactor = getSpeed() / hypotenuse;

			float xVel = xDir * convertingFactor;
			float yVel = yDir * convertingFactor;

			for (int i = 0; i < TOTAL_ENEMIES; i++)
			{
				if (eArray[i].isAlive())
				{
					if (willCollide(&xVel, &yVel, eArray[i].getHitbox()))
					{
						break;
					}
				}
			}

			float newX = getX() + xVel;
			float newY = getY() + yVel;

			if (newX < getHitbox().width / 2)
			{
				setX(getHitbox().width/2);
			}
			else if (newX > map->getWidth() - getHitbox().width / 2)
			{
				setX(map->getWidth() - getHitbox().width / 2);
			}
			else
			{
				setX(newX);
			}

			if (newY < getHitbox().height/2)
			{
				setY(getHitbox().height / 2);
			}
			else if (newY > map->getHeight() - getHitbox().height / 2)
			{
				setY(map->getHeight() - getHitbox().height / 2);
			}
			else
			{
				setY(newY);
			}
		}

		updateHitbox();
	}
}

void Player::shoot(SDL_Renderer* renderer, Map* map, ScreenDimensions screen, MouseCoordinates mouse,
	Enemy eArray[], WeaponStats stats)
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
				int xDif = mouse.x - (map->getX() + getX());
				int yDif = mouse.y - (map->getY() + getY());
				double hypotenus = hypot((double)xDif, (double)yDif);
				double convertingFactor = 1 / hypotenus;

				float x1, y1, x2, y2, xUnit, yUnit;
				x1 = (float)(map->getX() + getX());
				y1 = (float)(map->getY() + getY());
				x2 = (float)(x1 + xDif * convertingFactor);
				y2 = (float)(y1 + yDif * convertingFactor);
				xUnit = x2 - x1;
				yUnit = y2 - y1;

				while ((x1 >= map->getX() && x1 <= map->getX() + map->getWidth()) &&
					(y1 >= map->getY() && y1 <= map->getY() + map->getHeight()))
				{
					SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
					SDL_RenderDrawLineF(renderer, x1 + 1, y1 + 1, x2 + 1, y2 + 1);
					SDL_RenderDrawLineF(renderer, x1 - 1, y1 - 1, x2 - 1, y2 - 1);
					SDL_RenderDrawLineF(renderer, x1 + 1, y1 - 1, x2 + 1, y2 - 1);
					SDL_RenderDrawLineF(renderer, x1 - 1, y1 + 1, x2 - 1, y2 + 1);
					SDL_RenderDrawLineF(renderer, x1 + 2, y1 + 2, x2 + 2, y2 + 2);
					SDL_RenderDrawLineF(renderer, x1 - 2, y1 - 2, x2 - 2, y2 - 2);
					SDL_RenderDrawLineF(renderer, x1 + 2, y1 - 2, x2 + 2, y2 - 2);
					SDL_RenderDrawLineF(renderer, x1 - 2, y1 + 2, x2 - 2, y2 + 2);

					x1 += xUnit;
					x2 += xUnit;
					y1 += yUnit;
					y2 += yUnit;

					collidingGrunt = checkPointCollide((int)x1, (int)y1, eArray, map);
					if (collidingGrunt >= 0)
					{
						break;
					}
				}
			}

			if (collidingGrunt >= 0)
			{
				eArray[collidingGrunt].incrementHealth(-stats.getGunDamage(getGun()));
			}

			Uint32 fireRateMilliseconds = (Uint32)(1000 /
				stats.getGunFireRate(PISTOL));
			gunTimer.markTimer(fireRateMilliseconds);
		}
	}
}

void Player::render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
	ScreenDimensions screen, Map* map)
{
	if (isAlive())
	{
		SDL_Rect renderClip = { map->getX() + getX() - spriteClip.w / 2, map->getY() + getY() - spriteClip.h / 2, 
			spriteClip.w, spriteClip.h };

		SDL_RenderCopy(renderer, spriteSheet, &spriteClip, &renderClip);
	}
}

double Player::distanceTo(int x, int y)
{
	double xDif = (double)(x - getX());
	double yDif = (double)(y - getY());
	return hypot(xDif, yDif);
}

int Player::checkPointCollide(int x, int y, Enemy eArray[], Map* map)
{
	int closestIndex = -1;
	double smallestDistance = -1.f;
	double currentDistance;
	int currentLeft;
	int currentRight;
	int currentTop;
	int currentBottom;
	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (eArray[i].isAlive())
		{
			// Added map positions since the positions of grunts are relative to the map, but the point in quesiton is relative to the renderer.
			currentLeft = map->getX() + eArray[i].getX() - eArray[i].getHitbox().width / 2;
			currentRight = map->getX() + eArray[i].getX() + eArray[i].getHitbox().width / 2;
			currentTop = map->getY() + eArray[i].getY() - eArray[i].getHitbox().height / 2;
			currentBottom = map->getY() + eArray[i].getY() + eArray[i].getHitbox().height / 2;

			// If the point is in the hitbox
			if ((x >= currentLeft && x <= currentRight) && (y >= currentTop && y <= currentBottom))
			{
				currentDistance = distanceTo(eArray[i].getX(), eArray[i].getY());
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
