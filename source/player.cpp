#include "..\headers\player.h"

Player::Player(SDL_Renderer* r, Map* map, WeaponStats stats, float x, float y,
	int mHealth, int s, int w, int h, int gun, int melee)
{
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
	this->gun = gun;
	this->meleeWeapon = melee;

	playerState = PLAYER_NOT_ATTACKING;

	gunTimer = Timer();

	meleeTimer = Timer();
	// printf("%f, %f.\n", stats.getMeleeRange(melee), stats.getMeleeAngle(melee));
	meleeCone = ConeRays(x, y, stats.getMeleeRange(melee), stats.getMeleeAngle(melee) * M_PI / 180, 0);

	setRenderer(r);
	setMap(map);
}

void Player::move(bool* states, Enemy eArray[])
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
						
					}
				}
			}

			float newX = getX() + xVel;
			float newY = getY() + yVel;

			if (newX < getHitbox()->width / 2)
			{
				setX(getHitbox()->width/2);
			}
			else if (newX > getMap()->getWidth() - getHitbox()->width / 2)
			{
				setX(getMap()->getWidth() - getHitbox()->width / 2);
			}
			else
			{
				setX(newX);
			}

			if (newY < getHitbox()->height/2)
			{
				setY(getHitbox()->height / 2);
			}
			else if (newY > getMap()->getHeight() - getHitbox()->height / 2)
			{
				setY(getMap()->getHeight() - getHitbox()->height / 2);
			}
			else
			{
				setY(newY);
			}
		}

		updateHitbox();
		meleeCone.move(getX(), getY());
	}
}

void Player::shoot(ScreenDimensions screen, MouseCoordinates mouse,
	Enemy eArray[], WeaponStats stats, Hitbox* enemyHitboxes[])
{
	if (isAlive())
	{
		if (gunTimer.isTimerOn())
		{
			playerState = PLAYER_NOT_ATTACKING;
			gunTimer.updateTime();
		}
		else
		{
			if ((mouse.x > 0 && mouse.x < screen.width) && (mouse.y > 0 && mouse.y < screen.height))
			{
				playerState = PLAYER_SHOOTING;
				SDL_SetRenderDrawColor(getRenderer(), 215, 215, 0, 0xFF);
				float xMouseDif = (float)mouse.x - ((float)getMap()->getX() + getX());
				float yMouseDif = (float)mouse.y - ((float)getMap()->getY() + getY());

				float mouseAngle = atan2f(yMouseDif, xMouseDif);
				// printf("xDif: %f, yDif: %f\n", xDif, yDif);

				int collidingGrunt;
				float randomAngle;
				float shootAngle;

				float xDif, yDif;
				float x1, y1, x2, y2;
				for (int i = 0; i < stats.getGunPelletNum(gun); i++)
				{
					collidingGrunt = -1;
					randomAngle = (float)(rand() % (int)(stats.getGunAngle(gun) * 100)) / 100;
					randomAngle = randomAngle / 180 * M_PI;
					// printf("Random angle: %f\n", randomAngle);

					shootAngle = mouseAngle - stats.getGunAngle(gun) / 180 * M_PI / 2;
					shootAngle += randomAngle;

					xDif = cosf(shootAngle);
					yDif = sinf(shootAngle);

					x1 = (float)getMap()->getX() + getX();
					y1 = (float)getMap()->getY() + getY();
					x2 = x1 + xDif;
					y2 = y1 + yDif;

					while ((x1 >= getMap()->getX() && x1 <= getMap()->getX() + getMap()->getWidth()) &&
						(y1 >= getMap()->getY() && y1 <= getMap()->getY() + getMap()->getHeight()))
					{
						SDL_RenderDrawLineF(getRenderer(), x1, y1, x2, y2);
						SDL_RenderDrawLineF(getRenderer(), x1 + 1, y1 + 1, x2 + 1, y2 + 1);
						SDL_RenderDrawLineF(getRenderer(), x1 - 1, y1 - 1, x2 - 1, y2 - 1);
						SDL_RenderDrawLineF(getRenderer(), x1 + 1, y1 - 1, x2 + 1, y2 - 1);
						SDL_RenderDrawLineF(getRenderer(), x1 - 1, y1 + 1, x2 - 1, y2 + 1);
						/*
						SDL_RenderDrawLineF(getRenderer(), x1 + 2, y1 + 2, x2 + 2, y2 + 2);
						SDL_RenderDrawLineF(getRenderer(), x1 - 2, y1 - 2, x2 - 2, y2 - 2);
						SDL_RenderDrawLineF(getRenderer(), x1 + 2, y1 - 2, x2 + 2, y2 - 2);
						SDL_RenderDrawLineF(getRenderer(), x1 - 2, y1 + 2, x2 - 2, y2 + 2);
						*/

						x1 += xDif;
						x2 += xDif;
						y1 += yDif;
						y2 += yDif;

						collidingGrunt = checkPointCollide((int)x1, (int)y1, eArray);
						if (collidingGrunt >= 0)
						{
							break;
						}
					}

					if (collidingGrunt >= 0)
					{
						eArray[collidingGrunt].incrementHealth(-stats.getGunDamage(getGun()));
						eArray[collidingGrunt].moveFrom(getX(), getY(), stats.getGunKnockback(gun),
							getHitbox(), enemyHitboxes);
					}
				}
			}

			Uint32 fireRateMilliseconds = (Uint32)(1000 /
				stats.getGunFireRate(gun));
			gunTimer.markTimer(fireRateMilliseconds);
		}
	}
}

void Player::melee(Enemy eArray[], WeaponStats stats, Hitbox* enemyHitboxes[])
{
	if (meleeTimer.isTimerOn())
	{
		playerState = PLAYER_NOT_ATTACKING;
		meleeTimer.updateTime();
	}
	else
	{
		playerState = PLAYER_MELEEING;
		for (int i = 0; i < TOTAL_ENEMIES; i++)
		{
			if (eArray[i].isAlive())
			{
				if (meleeCone.checkCollision(*eArray[i].getHitbox()))
				{
					// printf("Melee hit.\n");
					eArray[i].incrementHealth(-stats.getMeleeDamage(meleeWeapon));
					eArray[i].moveFrom(getX(), getY(), stats.getMeleeKnockback(meleeWeapon),
						getHitbox(), enemyHitboxes);
				}
			}
		}
		meleeTimer.markTimer(1000 / stats.getMeleeSwingRate(meleeWeapon));
	}
}

void Player::render(SDL_Texture* spriteSheet, SDL_Rect spriteClip,
	ScreenDimensions screen)
{
	if (isAlive())
	{
		SDL_Rect renderClip = { getMap()->getX() + getX() - spriteClip.w / 2, getMap()->getY() + getY() - spriteClip.h / 2, 
			spriteClip.w, spriteClip.h };

		SDL_RenderCopy(getRenderer(), spriteSheet, &spriteClip, &renderClip);
	}
}

void Player::renderGun(SDL_Texture* gunSpriteSheet[], SDL_Rect* gunSpriteClips[])
{
	if (isAlive())
	{
		double xDif = cos(meleeCone.coneDirection);
		double yDif = sin(meleeCone.coneDirection);
		SDL_FPoint centre = { -25, gunSpriteClips[gun][GUN_IDLE].h / 2 };
		SDL_FRect renderClip = { getMap()->getX() + getX() + 25, getMap()->getY() + getY() - gunSpriteClips[gun][GUN_IDLE].h / 2, 
			gunSpriteClips[gun][GUN_IDLE].w, gunSpriteClips[gun][GUN_IDLE].h };

		if (playerState == PLAYER_SHOOTING)
		{
			SDL_RenderCopyExF(getRenderer(), gunSpriteSheet[gun], &gunSpriteClips[gun][GUN_FIRING], &renderClip,
				meleeCone.coneDirection * 180 / M_PI, &centre, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyExF(getRenderer(), gunSpriteSheet[gun], &gunSpriteClips[gun][GUN_IDLE], &renderClip,
				meleeCone.coneDirection * 180 / M_PI, &centre, SDL_FLIP_NONE);
		}
	}
}

int Player::checkPointCollide(int x, int y, Enemy eArray[])
{
	int closestIndex = -1;
	float smallestDistance = -1.f;
	float currentDistance;
	int currentLeft;
	int currentRight;
	int currentTop;
	int currentBottom;
	for (int i = 0; i < TOTAL_ENEMIES; i++)
	{
		if (eArray[i].isAlive())
		{
			// Added map positions since the positions of grunts are relative to the map, but the point in quesiton is relative to the renderer.
			currentLeft = getMap()->getX() + eArray[i].getX() - eArray[i].getHitbox()->width / 2;
			currentRight = getMap()->getX() + eArray[i].getX() + eArray[i].getHitbox()->width / 2;
			currentTop = getMap()->getY() + eArray[i].getY() - eArray[i].getHitbox()->height / 2;
			currentBottom = getMap()->getY() + eArray[i].getY() + eArray[i].getHitbox()->height / 2;

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

void Player::updateCone(MouseCoordinates mouse)
{
	meleeCone.changeDirection((float)(mouse.x - getMap()->getX()), (float)(mouse.y - getMap()->getY()));
	// printf("%d, %d.\n", mouse.x - map->getX(), mouse.y - map->getY());
}

void Player::drawCone()
{
	meleeCone.draw(getRenderer(), getMap());
}

int Player::getGun()
{
	return gun;
}

int Player::getMelee()
{
	return meleeWeapon;
}

int Player::getState()
{
	return playerState;
}

Timer Player::getGunTimer()
{
	return gunTimer;
}

Timer Player::getMeleeTimer()
{
	return meleeTimer;
}

void Player::setState(int s)
{
	playerState = s;
}

void Player::setGun(int newGun)
{
	gun = newGun;
}

void Player::setMelee(int newMelee)
{
	meleeWeapon = newMelee;
}
