#include <mLine.h>
#include <iostream>

mLine::mLine(float a, float b, float c, float d)
{
	x1 = a;
	y1 = b;
	x2 = c;
	y2 = d;
	length = hypotf(c - a, d - b);
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
	// printf("Length: %f, (%f, %f) -> (%f, %f).\n", length, x1, y1, x2, y2);
	float hitboxLeft = hitbox.xPos;
	float hitboxRight = hitbox.xPos + (float)hitbox.width;
	float hitboxTop = hitbox.yPos;
	float hitboxBottom = hitbox.yPos + (float)hitbox.height;

	float deg = atan2f(y2 - y1, x2 - x1);

	float intervalLength = 10;
	float intervalX = cosf(deg) * intervalLength;
	float intervalY = sinf(deg) * intervalLength;
	// printf("intervalX: %f, intervalY: %f, deg: %f.\n", intervalX, intervalY, deg);
	float checkX = x1;
	float checkY = y1;

	for (float i = 0; i <= length; i += intervalLength)
	{
		// printf("(%f, %f).\n", checkX, checkY);
		if ((checkX >= hitboxLeft && checkX <= hitboxRight) && (checkY >= hitboxTop && checkY <= hitboxBottom))
		{
			return true;
		}
		checkX += intervalX;
		checkY += intervalY;
	}

	return false;
}