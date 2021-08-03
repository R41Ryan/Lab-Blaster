#include <hitbox.h>

void Hitbox::update(float x, float y)
{
	xPos = x - width / 2;
	yPos = y - height / 2;
}
