#include <userInterface.h>

UserInterface::UserInterface(Player* p, Map* m, SDL_Renderer* r)
{
	player = p;
	map = m;
	renderer = r;
}

void UserInterface::displayHealth(ScreenDimensions sd)
{
	float xOffset = 10;
	float yOffset = 10;
	float barWidth = sd.width * 1/3;
	float remainingHealthBarWidth = (float)player->getCurrentHealth() / (float)player->getMaxHealth() * barWidth;
	float barHeight = sd.height / 20;
	for (float i = 0; i < barHeight; i += 1)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
		SDL_RenderDrawLineF(renderer, xOffset, yOffset + i, xOffset + barWidth, yOffset + i);
		SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);
		SDL_RenderDrawLineF(renderer, xOffset, yOffset + i, xOffset + remainingHealthBarWidth, yOffset + i);
	}
}

Player* UserInterface::getPlayer()
{
	return player;
}

Map* UserInterface::getMap()
{
	return map;
}

SDL_Renderer* UserInterface::getRenderer()
{
	return renderer;
}

void UserInterface::setPlayer(Player* p)
{
	player = p;
}

void UserInterface::setMap(Map* m)
{
	map = m;
}

void UserInterface::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}
