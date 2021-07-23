class Character
{
private:
	int xPos;
	int yPos;
	int maxHealth;
	int currentHealth;
	bool living;
public:
	// Constructors
	Character(int x = 0, int y = 0, int mHealth = 0);

	// Functions
	// Change the xPos by x units, and the yPos by y units.
	void move(int x, int y);
	// Increment the character's health by h points. Negative units are allowed. Health cannot be greater than max or less than 0.
	void incrementHealth(int h);
	// Restores the character's health to maxHealth.
	void restoreHealth();

	// Getter Functions
	int getX();
	int getY();
	int getMaxHealth();
	int getCurrentHealth();
	bool isAlive();

	// Setter Functions
	void setX(int x);
	void setY(int y);
	void setMaxHealth(int mHealth);
	void setCurrentHealth(int cHealth);
};