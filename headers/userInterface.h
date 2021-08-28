#pragma once
#include <player.h>
#include <enemy.h>
#include <screenDimensions.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

class UserInterface 
{
private:
	Player* player;
	Map* map;
	SDL_Renderer* renderer;

	SDL_Texture* equippedGunDisplay[TOTAL_GUN_TYPES];
	float gunTextureWidths[TOTAL_GUN_TYPES];
	float gunTextureHeights[TOTAL_GUN_TYPES];

	SDL_Texture* equippedMeleeDisplay[TOTAL_MELEE_TYPES];
	float meleeTextureWidths[TOTAL_MELEE_TYPES];
	float meleeTextureHeights[TOTAL_MELEE_TYPES];
public:
	// Constructors

	UserInterface(Player* p, Map* m, SDL_Renderer* r, TTF_Font* textFont);

	// Functions

	// modifies the index of the equipped gun array (given by gun) of textures, created from the given font using the given message and SDL_Color.
	void loadRenderedGunText(TTF_Font* font, std::string textureText, SDL_Color textColor, int gun);

	// modifies the index of the equipped melee arrays (given by gun) of textures, created from the given font using the given message and SDL_Color.
	void loadRenderedMeleeText(TTF_Font* font, std::string textureText, SDL_Color textColor, int melee);

	// Fills in the equippedGunDisplay array with rendered text textures for each of the guns.
	void fillGunDisplays(TTF_Font* font);

	// Fills in the equippedMeleeDisplay array with rendered text textures for each of the guns.
	void fillMeleeDisplays(TTF_Font* font);

	// Displays the player's current health as a health bar shown at the top-left of the rendering screen.
	void displayHealth(ScreenDimensions sd);

	// Displays what gun the player currently has equipped on the screen.
	void displayGun(ScreenDimensions sd);

	// Displays what melee the player currently has equipped on the screen.
	void displayMelee(ScreenDimensions sd);

	// Getters

	Player* getPlayer();
	Map* getMap();
	SDL_Renderer* getRenderer();
	SDL_Texture** getEquippedGunDisplay();

	// Setters

	void setPlayer(Player* p);
	void setMap(Map* m);
	void setRenderer(SDL_Renderer* r);
};