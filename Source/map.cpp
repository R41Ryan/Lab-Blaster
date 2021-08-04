#include <map.h>

Map::Map()
{
	floor = NULL;
	xPos = 0;
	yPos = 0;
	width = 0;
	height = 0;
}

Map::~Map()
{
	free();
}

void Map::free()
{
	if (floor != NULL)
	{
		SDL_DestroyTexture(floor);
		floor = NULL;
		width = 0;
		height = 0;
	}
}

bool Map::loadFloor(SDL_Renderer* renderer, std::string path)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	
	if (loadedSurface == NULL)
	{
		printf("Failed to load floor image: %s. IMG_ERROR: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to convert loaded floor surface to texture. SDL_ERROR: %s\n", SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	floor = newTexture;
	
	return floor != NULL;
}

void Map::render(SDL_Renderer* renderer)
{
	if (floor != NULL)
	{
		SDL_Rect renderRect = { xPos, yPos, width, height };

		SDL_RenderCopy(renderer, floor, NULL, &renderRect);
	}
	else
	{
		printf("Map floor cannot be found!\n");
	}
}

void Map::setCentrePlayer(float playerX, float playerY, ScreenDimensions screen)
{
	xPos = screen.width / 2 - playerX;
	yPos = screen.height / 2 - playerY;

	if (xPos > 0)
	{
		xPos = 0;
	}
	else if (xPos < screen.width - width)
	{
		xPos = screen.width - width;
	}

	if (yPos > 0)
	{
		yPos = 0;
	}
	else if (yPos < screen.height - height)
	{
		yPos = screen.height - height;
	}
}

SDL_Texture* Map::getFloor()
{
	return floor;
}

int Map::getX()
{
	return xPos;
}

int Map::getY()
{
	return yPos;
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}

void Map::setX(int x)
{
	xPos = x;
}

void Map::setY(int y)
{
	yPos = y;
}
