#include <userInterface.h>

UserInterface::UserInterface(Player* p, Map* m, SDL_Renderer* r, TTF_Font* textFont)
{
	player = p;
	map = m;
	renderer = r;

	fillGunDisplays(textFont);
	fillMeleeDisplays(textFont);
}

void UserInterface::loadRenderedGunText(TTF_Font* font, std::string textureText, SDL_Color textColor, int gun)
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

void UserInterface::loadRenderedMeleeText(TTF_Font* font, std::string textureText, SDL_Color textColor, int melee)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface. TTF_ERROR: %s.\n", TTF_GetError());
	}
	else
	{
		equippedMeleeDisplay[melee] = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (equippedMeleeDisplay[melee] == NULL)
		{
			printf("Unable to create texture from surface. SDL_ERROR: %s.\n", SDL_GetError());
		}
		else
		{
			meleeTextureWidths[melee] = textSurface->w;
			meleeTextureHeights[melee] = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void UserInterface::fillGunDisplays(TTF_Font* font)
{
	SDL_Color color = { 0, 0, 0, 0xFF };
	loadRenderedGunText(font, "GUN: Pistol", color, PISTOL);
	loadRenderedGunText(font, "GUN: Shotgun", color, SHOTGUN);
	loadRenderedGunText(font, "GUN: SMG", color, SMG);
	loadRenderedGunText(font, "GUN: Sniper", color, SNIPER);
	loadRenderedGunText(font, "GUN: Machine Gun", color, MACHINE_GUN);
}

void UserInterface::fillMeleeDisplays(TTF_Font* font)
{
	SDL_Color color = { 0, 0, 0, 0xFF };
	loadRenderedMeleeText(font, "MELEE: Fists", color, FISTS);
	loadRenderedMeleeText(font, "MELEE: Knife", color, KNIFE);
	loadRenderedMeleeText(font, "MELEE: Baseball Bat", color, BASEBALL_BAT);
	loadRenderedMeleeText(font, "MELEE: Sword", color, SWORD);
	loadRenderedMeleeText(font, "MELEE: Chainsaw", color, CHAINSAW);
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

void UserInterface::displayGun(ScreenDimensions sd)
{
	float xOffset = 10;
	float yOffset = sd.height / 20 + 20;

	SDL_SetRenderDrawColor(renderer, 0x99, 0xFF, 0xFF, 0xFF);
	SDL_Rect squareRenderRect = { xOffset, yOffset - 5, gunTextureWidths[player->getGun()] + 10,
		gunTextureHeights[player->getGun()] + 10 };
	SDL_RenderFillRect(renderer, &squareRenderRect);

	SDL_Rect textRenderRect = { xOffset + 5, yOffset, gunTextureWidths[player->getGun()], gunTextureHeights[player->getGun()] };
	// printf("%d.\n", player->getMelee());
	// printf("%f, %f.\n", meleeTextureWidths[player->getMelee()], meleeTextureHeights[player->getMelee()]);
	SDL_RenderCopy(renderer, equippedGunDisplay[player->getGun()], NULL, &textRenderRect);
}

void UserInterface::displayMelee(ScreenDimensions sd)
{
	float xOffset = 10;
	float yOffset = sd.height / 20 + gunTextureHeights[player->getGun()] + 35;

	SDL_SetRenderDrawColor(renderer, 0x99, 0xFF, 0xFF, 0xFF);
	SDL_Rect squareRenderRect = { xOffset, yOffset - 5, meleeTextureWidths[player->getMelee()] + 10,
		meleeTextureHeights[player->getMelee()] + 10 };
	SDL_RenderFillRect(renderer, &squareRenderRect);

	SDL_Rect textRenderRect = { xOffset + 5, yOffset, meleeTextureWidths[player->getMelee()], gunTextureHeights[player->getMelee()] };
	// printf("%d.\n", player->getGun());
	// printf("%f, %f.\n", gunTextureWidths[player->getGun()], gunTextureHeights[player->getGun()]);
	SDL_RenderCopy(renderer, equippedMeleeDisplay[player->getMelee()], NULL, &textRenderRect);
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
