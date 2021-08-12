#include <ConeRays.h>

ConeRays::ConeRays(float xStart, float yStart, float rayLength, double deg, double dir)
{
	coneDirection = dir;
	coneDegrees = deg;
	range = rayLength;
	centreX = xStart;
	centreY = yStart;

	if (deg == 0)
	{
		numRays = 1;
	}
	else
	{
		numRays = abs((int)(deg * 180 / M_PI));
	}

	// printf("coneDirection: %f, coneDegrees: %f, range: %f, centre: (%f, %f), numeRays: %d.\n",
		// coneDirection, coneDegrees, range, centreX, centreY, numRays);

	fillLines();
}

ConeRays::~ConeRays()
{
	coneDegrees = 0;
	coneDirection = 0;
	range = 0;
	centreX = 0;
	centreY = 0;
	numRays = 0;
	lines.clear();
}

void ConeRays::draw(SDL_Renderer* renderer, Map* map)
{
	for (int i = 0; i < numRays; i++)
	{
		// printf("Drawing line %d. numRays: %d.\n", i, numRays);
		lines[i].draw(renderer, map);
	}
}

void ConeRays::move(float x, float y)
{
	float xDif = x - centreX;
	float yDif = y - centreY;

	for (int i = 0; i < numRays; i++)
	{
		lines[i].x1 += xDif;
		lines[i].y1 += yDif;
		lines[i].x2 += xDif;
		lines[i].y2 += yDif;
	}

	centreX += xDif;
	centreY += yDif;
}

void ConeRays::changeDirection(float x, float y)
{
	float dir = atan2f(y - centreY, x - centreX);
	/*
	if (x - centreX < 0)
	{
		dir += M_PI;
	}
	*/

	// printf("%f\n", dir);

	coneDirection = dir;

	lines.clear();
	fillLines();
}

bool ConeRays::checkCollision(Hitbox hitbox)
{
	for (int i = 0; i < numRays; i++)
	{
		if (lines[i].checkCollision(hitbox))
		{
			return true;
		}
	}

	return false;
}

void ConeRays::fillLines()
{
	double currentLineAngle = coneDirection - coneDegrees / 2;
	// printf("%f, %f, %f\n", coneDirection, coneDegrees, currentLineAngle);
	float currentLengthX, currentLengthY;
	for (int i = 0; i < numRays; i++)
	{
		currentLengthX = cosf(currentLineAngle) * range;
		currentLengthY = sinf(currentLineAngle) * range;
		mLine lineToAdd = { centreX, centreY, centreX + currentLengthX, centreY + currentLengthY };
		lines.push_back(lineToAdd);
		currentLineAngle += M_PI / 180;
	}
}
