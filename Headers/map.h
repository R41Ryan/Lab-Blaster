#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>
#include <screenDimensions.h>
#include <mouseCoordinates.h>

enum mapAssets
{
	FLOOR,
	TOTAL_MAP_ASSETS
};

class Map
{
private:
	SDL_Texture* floor;
	int xPos;
	int yPos;
	int width;
	int height;
public:
	// Constructor
	Map();
	~Map();

	// Functions
	// Deallocates the current floor texture if it exists.
	void free();
	// Loads the texture given by the path as the floor, and modifies the width and height to match that of the floor. Returns false if unsucessful.
	bool loadFloor(SDL_Renderer* renderer, std::string path);
	// Renders the map.
	void render(SDL_Renderer* renderer);
	// Set the x and y rendering position of the map such that it is between the player's location on the map and the mouse.
	void setCentrePlayer(float playerX, float playerY, ScreenDimensions screen, MouseCoordinates mouse);
	// Getters
	SDL_Texture* getFloor();
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// Setters
	void setX(int x);
	void setY(int y);
};