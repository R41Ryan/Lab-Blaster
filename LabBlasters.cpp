#include <player.h>
#include <enemy.h>
#include <map.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <screenDimensions.h>

const ScreenDimensions SCREEN_DIMENSIONS(800, 600);

const int TOTAL_GRUNTS = 1;

SDL_Window* gameWindow = NULL;

SDL_Renderer* gameRenderer = NULL;

SDL_Rect* spriteClips[TOTAL_CHARACTER_TYPES];
SDL_Texture* characterSpriteSheets[TOTAL_CHARACTER_TYPES];

WeaponStats stats = WeaponStats();
Map gameMap;
MouseCoordinates mouse = MouseCoordinates();

bool keyStates[TOTAL_KEYS];
bool mouseStates[TOTAL_MOUSE_BUTTONS];

int characterArraySizes[TOTAL_CHARACTER_TYPES];

Enemy arrEnemy[TOTAL_GRUNTS];

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		printf("SDL failed to initialize. SDL_ERROR: %s\n", SDL_GetError());
	}
	else
	{
		gameWindow = SDL_CreateWindow("Lab Blasters", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_DIMENSIONS.width, 
			SCREEN_DIMENSIONS.height, SDL_WINDOW_SHOWN);
		if (gameWindow == NULL)
		{
			printf("Failed to create window. SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gameRenderer == NULL)
			{
				printf("Failed to create renderer. SDL_ERROR: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) && imgFlags))
				{
					printf("Failed to initialize SDL_IMG. IMG_ERROR: %s\n", IMG_GetError());
					success = false;
				}
				
				if (TTF_Init() == -1)
				{
					printf("Failed to initialize SDL_TTF. TTF_ERROR: %s\n", TTF_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("Failed to initialize SDL_MIXER. Mix_ERROR: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void setupClips()
{
	// Setting up player sprites
	spriteClips[PLAYER] = new SDL_Rect[PLAYER_TOTAL_SPRITES];
	spriteClips[PLAYER][PLAYER_IDLE].x = 0;
	spriteClips[PLAYER][PLAYER_IDLE].y = 0;
	spriteClips[PLAYER][PLAYER_IDLE].w = 50;
	spriteClips[PLAYER][PLAYER_IDLE].h = 50;
	
	// Setting up grunt sprites
	spriteClips[GRUNT] = new SDL_Rect[GRUNT_TOTAL_SPRITES];
	spriteClips[GRUNT][GRUNT_IDLE].x = 0;
	spriteClips[GRUNT][GRUNT_IDLE].y = 0;
	spriteClips[GRUNT][GRUNT_IDLE].w = 50;
	spriteClips[GRUNT][GRUNT_IDLE].h = 50;
}

bool loadSpriteSheet(SDL_Texture* spriteSheet[], std::string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Failed to load image %s. IMG_ERROR: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, 1, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(gameRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to convert surface to texture. SDL_ERROR: %s \n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	*spriteSheet = newTexture;
	return spriteSheet != NULL;
}

bool loadSpriteSheets()
{
	bool success = true;

	if (!loadSpriteSheet(&characterSpriteSheets[PLAYER], "sprites/player.png"))
	{
		printf("Failed to load player sprite sheet.\n");
		success = false;
	}

	if (!loadSpriteSheet(&characterSpriteSheets[GRUNT], "sprites/grunt.png"))
	{
		printf("Failed to load player sprite sheet.\n");
		success = false;
	}

	return success;
}

void close()
{
	for (int i = 0; i < TOTAL_CHARACTER_TYPES; i++)
	{
		SDL_DestroyTexture(characterSpriteSheets[i]);
		characterSpriteSheets[i] = NULL;
	}
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);
	gameRenderer = NULL;
	gameWindow = NULL;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void setKeyState(SDL_Keycode sym, bool state)
{
	switch (sym)
	{
	case SDLK_w:
		keyStates[KEY_W] = state;
		break;
	case SDLK_s:
		keyStates[KEY_S] = state;
		break;
	case SDLK_a:
		keyStates[KEY_A] = state;
		break;
	case SDLK_d:
		keyStates[KEY_D] = state;
		break;
	}
}

void setMouseState(SDL_MouseButtonEvent button, bool state)
{
	switch (button.button)
	{
	case SDL_BUTTON_LEFT:
		mouseStates[LEFT_MOUSE_BUTTON] = state;
		break;
	case SDL_BUTTON_RIGHT:
		mouseStates[RIGHT_MOUSE_BUTTON] = state;
		break;
	}
}

int main(int argc, char* argv[])
{
	for (int i = 0; i < TOTAL_KEYS; i++)
	{
		keyStates[i] = false;
	}

	if (!init())
	{
		printf("Failed to initialize.\n");
	}
	else
	{
		if (!loadSpriteSheets())
		{
			printf("Failed to load sprite sheets.\n");
		}
		else
		{
			setupClips();

			characterArraySizes[PLAYER] = 1;
			characterArraySizes[GRUNT] = TOTAL_GRUNTS;

			if (!gameMap.loadFloor(gameRenderer, "map/map_floor.png"))
			{
				printf("Failed to load floor.\n");
			}

			bool quit = false;

			Player gamePlayer = Player(0, (float)SCREEN_DIMENSIONS.width / 2, (float)SCREEN_DIMENSIONS.height / 2, 100,
				5, 50, 50, PISTOL, FISTS);

			for (int i = 0; i < sizeof(arrEnemy) / sizeof(Enemy); i++)
			{
				arrEnemy[i] = Enemy((float)(rand() % gameMap.getWidth()), (float)(rand() % gameMap.getHeight()),
					100, 3, 50, 50);
			}

			SDL_Event e;
			
			while (!quit)
			{
				mouse.update();

				while (SDL_PollEvent(&e) > 0)
				{
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;
					case SDL_KEYDOWN:
						setKeyState(e.key.keysym.sym, true);
						break;
					case SDL_KEYUP:
						setKeyState(e.key.keysym.sym, false);
						break;
					case SDL_MOUSEBUTTONDOWN:
						setMouseState(e.button, true);
						break;
					case SDL_MOUSEBUTTONUP:
						setMouseState(e.button, false);
						break;
					}
				}

				gamePlayer.move(keyStates, &gameMap);
				
				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gameRenderer);
				
				gameMap.setCentrePlayer(gamePlayer.getX(), gamePlayer.getY(), SCREEN_DIMENSIONS);
				gameMap.render(gameRenderer);

				for (int i = 0; i < sizeof(arrEnemy) / sizeof(Enemy); i++)
				{
					arrEnemy[i].move(gamePlayer.getX(), gamePlayer.getY());
				}
								
				if (mouseStates[LEFT_MOUSE_BUTTON])
				{
					gamePlayer.shoot(gameRenderer, &gameMap, SCREEN_DIMENSIONS, mouse, 
						arrEnemy, characterArraySizes, stats);
				}
				else
				{
					if (gamePlayer.getGunTimer().isTimerOn())
					{
						gamePlayer.getGunTimer().setTimerState(false);
					}
				}
				
				gamePlayer.render(gameRenderer, characterSpriteSheets[PLAYER], 
					spriteClips[PLAYER][PLAYER_IDLE], SCREEN_DIMENSIONS);
				
				for (int i = 0; i < sizeof(arrEnemy) / sizeof(Enemy); i++)
				{
					arrEnemy[i].render(gameRenderer, characterSpriteSheets[GRUNT],
						spriteClips[GRUNT][GRUNT_IDLE], &gameMap);
				}
				
				SDL_RenderPresent(gameRenderer);
			}
		}
		
	}

	close();

	return 0;
}