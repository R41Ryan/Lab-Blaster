#include <player.h>
#include <enemy.h>
#include <map.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <screenDimensions.h>
#include <time.h>
#include <userInterface.h>;

const ScreenDimensions SCREEN_DIMENSIONS(800, 600);

const int FRAME_RATE_CAP = 60;
Timer frameRateTimer = Timer();

SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

SDL_Rect* spriteClips[TOTAL_CHARACTER_TYPES];
SDL_Texture* characterSpriteSheets[TOTAL_CHARACTER_TYPES];

SDL_Rect* playerGunClips[TOTAL_GUN_TYPES];
SDL_Texture* playerGunSpriteSheets[TOTAL_GUN_TYPES];

TTF_Font* gameFont;

WeaponStats stats = WeaponStats();
Map gameMap;
MouseCoordinates mouse = MouseCoordinates();

bool keyStates[TOTAL_KEYS];
bool mouseStates[TOTAL_MOUSE_BUTTONS];

Enemy arrEnemy[TOTAL_ENEMIES];
Hitbox* enemyHitboxes[TOTAL_ENEMIES];

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
				else
				{
					gameFont = TTF_OpenFont("fonts/Nasa21-l23X.ttf", 28);
					if (gameFont == NULL)
					{
						printf("Failed to load Nasa21 Font. TTF_ERROR: %s.\n", TTF_GetError());
					}
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

	// Setting up pistol clips
	playerGunClips[PISTOL] = new SDL_Rect[TOTAL_GUN_STATES];
	playerGunClips[PISTOL][GUN_IDLE].x = 0;
	playerGunClips[PISTOL][GUN_IDLE].y = 12;
	playerGunClips[PISTOL][GUN_IDLE].w = 30;
	playerGunClips[PISTOL][GUN_IDLE].h = 10;
	playerGunClips[PISTOL][GUN_FIRING].x = 0;
	playerGunClips[PISTOL][GUN_FIRING].y = 42;
	playerGunClips[PISTOL][GUN_FIRING].w = 30;
	playerGunClips[PISTOL][GUN_FIRING].h = 10;

	// Setting up shotgun clips
	playerGunClips[SHOTGUN] = new SDL_Rect[TOTAL_GUN_STATES];
	playerGunClips[SHOTGUN][GUN_IDLE].x = 0;
	playerGunClips[SHOTGUN][GUN_IDLE].y = 0;
	playerGunClips[SHOTGUN][GUN_IDLE].w = 50;
	playerGunClips[SHOTGUN][GUN_IDLE].h = 10;
	playerGunClips[SHOTGUN][GUN_FIRING].x = 0;
	playerGunClips[SHOTGUN][GUN_FIRING].y = 10;
	playerGunClips[SHOTGUN][GUN_FIRING].w = 50;
	playerGunClips[SHOTGUN][GUN_FIRING].h = 10;
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

	if (!loadSpriteSheet(&playerGunSpriteSheets[PISTOL], "sprites/pistol.png"))
	{
		printf("Failed to load pistol sprite sheet.\n");
		success = false;
	}

	if (!loadSpriteSheet(&playerGunSpriteSheets[SHOTGUN], "sprites/shotgun.png"))
	{
		printf("Failed to load shotgun sprite sheet.\n");
	}
	return success;
}

void close()
{
	TTF_CloseFont(gameFont);
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
	case SDLK_p:
		keyStates[KEY_P] = state;
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
	srand(time(NULL)); // Initializes random number generator

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

			if (!gameMap.loadFloor(gameRenderer, "map/map_floor.png"))
			{
				printf("Failed to load floor.\n");
			}

			bool quit = false;

			Player gamePlayer = Player(gameRenderer, &gameMap, stats, (float)SCREEN_DIMENSIONS.width / 2,
				(float)SCREEN_DIMENSIONS.height / 2, 100, 5, 40, 40, SMG, SWORD);

			for (int i = 0; i < TOTAL_GRUNTS; i++)
			{
				arrEnemy[i] = Enemy(gameRenderer, &gameMap, GRUNT, (float)(rand() % gameMap.getWidth()),
					(float)(rand() % gameMap.getHeight()), 100, 3, 40, 40);
				enemyHitboxes[i] = arrEnemy[i].getHitbox();
			}

			UserInterface gameUI = UserInterface(&gamePlayer, &gameMap, gameRenderer, gameFont);
			
			SDL_Event e;
			
			while (!quit)
			{
				frameRateTimer.markTimer((Uint32)(1000 / FRAME_RATE_CAP));
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

				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gameRenderer);
				
				if (gamePlayer.isAlive())
				{
					gameMap.setCentrePlayer(gamePlayer.getX(), gamePlayer.getY(), SCREEN_DIMENSIONS,
						mouse);
				}
				gameMap.render(gameRenderer);
				SDL_SetRenderDrawColor(gameRenderer, 0, 0xFF, 0, 0xFF);

				for (int i = 0; i < TOTAL_ENEMIES; i++)
				{
					if (arrEnemy[i].isAlive())
					{
						if (arrEnemy[i].updateAttackState(gamePlayer.getHitbox()))
						{
							gamePlayer.incrementHealth(-GRUNT_DAMAGE);
						}
						else if (arrEnemy[i].getEnemyState() == ENEMY_STATE_NOT_ATTACKING)
						{
							if (gamePlayer.isAlive())
							{
								arrEnemy[i].moveTo(gamePlayer.getX(), gamePlayer.getY(),
									arrEnemy[i].getSpeed(), gamePlayer.getHitbox(), enemyHitboxes);
							}
						}
					}
				}

				gamePlayer.move(keyStates, arrEnemy);
				gamePlayer.updateCone(mouse);
				
				if (keyStates[KEY_P])
				{
					gamePlayer.restoreHealth();
					for (int i = 0; i < TOTAL_ENEMIES; i++)
					{
						arrEnemy[i].spawn();
					}
				}

				if (mouseStates[LEFT_MOUSE_BUTTON])
				{
					gamePlayer.shoot(SCREEN_DIMENSIONS, mouse, 
						arrEnemy, stats, enemyHitboxes);
				}
				else
				{
					if (gamePlayer.getGunTimer().isTimerOn())
					{
						gamePlayer.getGunTimer().updateTime();
					}
				}

				if (mouseStates[RIGHT_MOUSE_BUTTON])
				{
					gamePlayer.melee(arrEnemy, stats, enemyHitboxes);
				}
				else
				{
					if (gamePlayer.getMeleeTimer().isTimerOn())
					{
						gamePlayer.getMeleeTimer().updateTime();
					}
				}
				
				gamePlayer.render(characterSpriteSheets[PLAYER], 
					spriteClips[PLAYER][PLAYER_IDLE], SCREEN_DIMENSIONS);
				// gamePlayer.renderGun(playerGunSpriteSheets, playerGunClips);
				// gamePlayer.drawHitbox(gameRenderer, &gameMap);
				// gamePlayer.drawCone(gameRenderer, &gameMap);
				
				for (int i = 0; i < TOTAL_ENEMIES; i++)
				{
					arrEnemy[i].render(characterSpriteSheets[GRUNT],
						spriteClips[GRUNT][GRUNT_IDLE]);
					// arrEnemy[i].drawHitbox(gameRenderer, &gameMap);
				}

				gameUI.displayHealth(SCREEN_DIMENSIONS);
				gameUI.displayGun(SCREEN_DIMENSIONS);
				gameUI.displayMelee(SCREEN_DIMENSIONS);

				SDL_RenderPresent(gameRenderer);

				int frameLoopCount = 0;

				while (frameRateTimer.isTimerOn())
				{
					frameRateTimer.updateTime();
					frameLoopCount = 0;
					if (frameLoopCount >= 1000)
					{
						printf("Frame Rate Timer malfunctioning. Ending program.\n");
						quit = true;
					}
					frameLoopCount++;
				}
			}
		}
		
	}

	close();

	return 0;
}