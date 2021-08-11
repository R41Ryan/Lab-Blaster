#include <mLine.h>
#include <iostream>

mLine::mLine(float a, float b, float c, float d)
{
	x1 = a;
	y1 = b;
	x2 = c;
	y2 = d;
	length = hypotf(a - b, c - d);
}

void mLine::draw(SDL_Renderer* renderer, Map* map)
{
	// printf("Drawing line. (%f, %f) -> (%f, %f).\n", x1, y1, x2, y2);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderDrawLineF(renderer, x1 + map->getX(), y1 + map->getY(),
		x2 + map->getX(), y2 + map->getY());
}

bool mLine::checkCollision(Hitbox hitbox)
{
	float hitboxLeft = hitbox.xPos;
	float hitboxRight = hitbox.xPos + (float)hitbox.width;
	float hitboxTop = hitbox.yPos;
	float hitboxBottom = hitbox.yPos + (float)hitbox.height;

	float deg = atan2f(y2 - y1, x2 - x1);
	if (x2 - x1 < 0)
	{
		deg += M_PI;
	}

	float intervalLength = 10;
	float intervalX = cosf(deg) * intervalLength;
	float intervalY = sinf(deg) * intervalLength;

	float checkX = x1;
	float checkY = y1;

	for (float i = 0; i <= length; i += intervalLength)
	{
		if ((checkX >= hitboxLeft && checkX <= hitboxRight) && (checkY >= hitboxTop && checkY <= hitboxBottom))
		{
			return true;
		}
		checkX += intervalX;
		checkY += intervalY;
	}

	return false;
}