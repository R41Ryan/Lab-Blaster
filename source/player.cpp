#include "..\headers\player.h"

Player::Player(int x, int y, int mHealth, int s, int gun, int melee)
{
	setX(x);
	setY(y);
	setMaxHealth(mHealth);
	setCurrentHealth(mHealth);
	setSpeed(s);
	shooting = false;
	meleeing = false;
	this->gun = gun;
	this->melee = melee;

	gunTimer = Timer();
	bulletFrameCounter = 0;
	bulletFrames = 4;

	meleeTimer = Timer();
}

void Player::move(bool* states, int mapWidth, int mapHeight)
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
		else if (newX > mapWidth)
		{
			setX(mapWidth);
		}
		else
		{
			setX(newX);
		}

		if (newY < 0)
		{
			setY(0);
		}
		else if (newY > mapHeight)
		{
			setY(mapHeight);
		}
		else
		{
			setY(newY);
		}
	}
}

void Player::shoot(SDL_Renderer* renderer, int screenWidth, int screenHeight, int mouseX, int mouseY,
	WeaponStats stats)
{
	if (gunTimer.isTimerOn())
	{
		gunTimer.updateTime();
	}
	else
	{
		if ((mouseX > 0 && mouseX < screenWidth) && (mouseY > 0 && mouseY < screenHeight))
		{
			SDL_SetRenderDrawColor(renderer, 215, 215, 0, 0xFF);
			int xDif = mouseX - screenWidth / 2;
			int yDif = mouseY - screenHeight / 2;
			double hypotenus = hypot((double)xDif, (double)yDif);
			double convertingFactor = 1 / hypotenus;

			float x1, y1, x2, y2, xUnit, yUnit;
			x1 = (float)(screenWidth / 2);
			y1 = (float)(screenHeight / 2);
			x2 = (float)(x1 + xDif * convertingFactor);
			y2 = (float)(y1 + yDif * convertingFactor);
			xUnit = x2 - x1;
			yUnit = y2 - y1;

			while ((x1 > 0 && x1 < screenWidth) && (y1 > 0 && y1 < screenHeight))
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
			}
		}

		// bulletFrameCounter++;

		Uint32 fireRateMilliseconds = (Uint32)(1000 /
			stats.getGunFireRate(PISTOL));
		gunTimer.markTimer(fireRateMilliseconds);
	}
}

void Player::render(SDL_Renderer* renderer, SDL_Texture* spriteSheet, SDL_Rect spriteClip,
	int screenWidth, int screenHeight)
{
	SDL_Rect renderClip = { screenWidth / 2 - spriteClip.w / 2, screenHeight / 2 - spriteClip.h / 2, spriteClip.w, spriteClip.h };

	SDL_RenderCopy(renderer, spriteSheet, &spriteClip, &renderClip);
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
