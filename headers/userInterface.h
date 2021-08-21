#pragma once
#include <player.h>
#include <enemy.h>
#include <screenDimensions.h>
#include <SDL_render.h>

class UserInterface 
{
private:
	Player* player;
	Map* map;
	SDL_Renderer* renderer;
public:
	// Constructors

	UserInterface(Player* p, Map* m, SDL_Renderer* r);

	// Functions

	// Displays the player's current health as a health bar shown at the top-left of the rendering screen.
	void displayHealth(ScreenDimensions sd);

	// Getters

	Player* getPlayer();
	Map* getMap();
	SDL_Renderer* getRenderer();

	// Setters

	void setPlayer(Player* p);
	void setMap(Map* m);
	void setRenderer(SDL_Renderer* r);
};