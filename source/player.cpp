#include "..\headers\player.h"

Player::Player(int x, int y, int mHealth, int s, int gun, int melee)
{
	setX(x);
	setY(y);
	setMaxHealth(mHealth);
	setCurrentHealth(mHealth);
	setSpeed(s);
	this->gun = gun;
	this->melee = melee;
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

		/*
		if (xDir == 0)
		{
			if (yDir == 1)
			{
				yVel = (float)getSpeed();
			}
			else if (yDir == -1)
			{
				yVel = (float)-getSpeed();
			}
		}
		else
		{
			double angle = atan(yDir / xDir);

			xVel = xDir * getSpeed() * cos(angle);
			yVel = yDir * abs(getSpeed() * sin(angle));
		}
		*/

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

void Player::shoot(int mouseX, int mouseY)
{

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

void Player::setGun(int newGun)
{
	gun = newGun;
}

void Player::setMelee(int newMelee)
{
	melee = newMelee;
}
