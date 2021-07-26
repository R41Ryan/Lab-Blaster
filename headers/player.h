#include <character.h>

enum playerFrames {
	PLAYER_IDLE,
	PLAYER_TOTAL_SPRITES
};

enum inputKeys {
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	TOTAL_KEYS
};

class Player : public Character
{
private:

public:
	// Constructors
	using Character::Character;
	// Functions
	// Takes in user input and moves the player character such that it is always moving at a set speed regardless of direction.
	void move(bool* states);
	// Getters

	// Setters
};