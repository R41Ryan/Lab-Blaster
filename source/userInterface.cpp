#include <userInterface.h>

UserInterface::UserInterface(Player* p, Map* m, SDL_Renderer* r, TTF_Font* textFont)
{
	player = p;
	map = m;
	renderer = r;

	fillGunDisplays(textFont);
}

void UserInterface::loadRenderedText(TTF_Font* font, std::string textureText, SDL_Color textColor, int gun)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface. TTF_ERROR: %s.\n", TTF_GetError());
	}
	else
	{
		equippedGunDisplay[gun] = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (equippedGunDisplay[gun] == NULL)
		{
			printf("Unable to create texture from surface. SDL_ERROR: %s.\n", SDL_GetError());
		}
		else
		{
			gunTextureWidths[gun] = textSurface->w;
			gunTextureHeights[gun] = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void UserInterface::fillGunDisplays(TTF_Font* font)
{
	SDL_Color color = { 0, 0, 0, 0xFF };
	loadRenderedText(font, "GUN: Pistol", color, PISTOL);
	loadRenderedText(font, "GUN: Shotgun", color, SHOTGUN);
	loadRenderedText(font, "GUN: SMG", color, SMG);
	loadRenderedText(font, "GUN: Sniper", color, SNIPER);
	loadRenderedText(font, "GUN: Machine Gun", color, MACHINE_GUN);
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

void UserInterface::displayWeapon(ScreenDimensions sd)
{
	float xOffset = 10;
	float yOffset = sd.height / 20 + 20;

	SDL_SetRenderDrawColor(renderer, 0x99, 0xFF, 0xFF, 0xFF);
	SDL_Rect squareRenderRect = { xOffset, yOffset - 5, gunTextureWidths[player->getGun()] + 10,
		gunTextureHeights[player->getGun()] + 10 };
	SDL_RenderFillRect(renderer, &squareRenderRect);

	SDL_Rect textRenderRect = { xOffset + 5, yOffset, gunTextureWidths[player->getGun()], gunTextureHeights[player->getGun()] };
	// printf("%d.\n", player->getGun());
	// printf("%f, %f.\n", gunTextureWidths[player->getGun()], gunTextureHeights[player->getGun()]);
	SDL_RenderCopy(renderer, equippedGunDisplay[player->getGun()], NULL, &textRenderRect);
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

SDL_Texture** UserInterface::getEquippedGunDisplay()
{
	return equippedGunDisplay;
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
