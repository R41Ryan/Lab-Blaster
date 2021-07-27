#include <player.h>
#include <enemy.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int SCREEN_WIDTH = 1008;
const int SCREEN_HEIGHT = 630;

SDL_Window* gameWindow = NULL;

SDL_Renderer* gameRenderer = NULL;

SDL_Rect playerSpriteClips[PLAYER_TOTAL_SPRITES];
SDL_Texture* characterSpriteSheets[TOTAL_CHARACTER_TYPES];

bool keyStates[TOTAL_KEYS];

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		printf("SDL failed to initialize. SDL_ERROR: %s\n", SDL_GetError());
	}
	else
	{
		gameWindow = SDL_CreateWindow("Lab Blasters", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	playerSpriteClips[PLAYER_IDLE].x = 0;
	playerSpriteClips[PLAYER_IDLE].y = 0;
	playerSpriteClips[PLAYER_IDLE].w = 50;
	playerSpriteClips[PLAYER_IDLE].h = 50;
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

			bool quit = false;

			Player* gamePlayer = new Player(0, 0, 100);

			SDL_Event e;

			while (!quit)
			{
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
					}
				}

				gamePlayer->move(keyStates);

				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gameRenderer);

				gamePlayer->render(gameRenderer, characterSpriteSheets[PLAYER], playerSpriteClips[PLAYER_IDLE]);

				SDL_RenderPresent(gameRenderer);
			}
		}
		
	}

	close();

	return 0;
}