#include "../headers/interactive.h"

Interactive::Interactive(float x, float y, float w, float h, SDL_Renderer* r, Map* m)
{
	xPos = x;
	yPos = y;
	iHitbox.active = true;
	iHitbox.width = w;
	iHitbox.height = h;
	iHitbox.xPos = x - w / 2;
	iHitbox.yPos = y - h / 2;

	renderer = r;
	map = m;
}

void Interactive::displayHitbox()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
	SDL_FRect renderRect = { map->getX() + iHitbox.xPos, map->getY() + iHitbox.yPos, iHitbox.width, iHitbox.height };
	SDL_RenderDrawRectF(renderer, &renderRect);
}

void Interactive::render(SDL_Texture* texture, SDL_Rect sourceClip)
{
	SDL_Rect renderRect = {map->getX() + xPos - iHitbox.width / 2, map->getY() + yPos - iHitbox.height / 2, iHitbox.width, iHitbox.height};
	SDL_RenderCopy(renderer, texture, &sourceClip, &renderRect);
}

bool Interactive::isColliding(Hitbox* targetHitbox)
{
	bool isLeft = targetHitbox->xPos + targetHitbox->width < iHitbox.xPos;
	bool isRight = targetHitbox->xPos > iHitbox.xPos + iHitbox.width;
	bool isAbove = targetHitbox->yPos + targetHitbox->height < iHitbox.yPos;
	bool isBelow = targetHitbox->yPos > iHitbox.yPos + iHitbox.height;
	if ((!isLeft && !isRight) && (!isAbove && !isBelow))
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Interactive::getX()
{
	return xPos;
}

float Interactive::getY()
{
	return yPos;
}

Hitbox* Interactive::getIHitbox()
{
	return &iHitbox;
}

void Interactive::setX(float x)
{
	xPos = x;
	iHitbox.xPos = x - iHitbox.width / 2;
}

void Interactive::setY(float y)
{
	yPos = y;
	iHitbox.yPos = y - iHitbox.height / 2;
}

void Interactive::setIHitbox(float w, float h)
{
	iHitbox.width = w;
	iHitbox.height = h;
	iHitbox.xPos = xPos - w / 2;
	iHitbox.yPos = yPos - h / 2;
}

void Interactive::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

void Interactive::setMap(Map* m)
{
	map = m;
}
