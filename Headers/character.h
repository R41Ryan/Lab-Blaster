class Character
{
private:
	int xPos;
	int yPos;
	int maxHealth;
	int currentHealth;
public:
	// Constructors
	Character();
	Character(int x, int y);
	Character(int x, int y, int mHealth);

	// Functions

	// Getter Functions
	int getX();
	int getY();
	int getMaxHealth();
	int getCurrentHealth();

	// Setter Functions
	void setX(int x);
	void setY(int y);
	void setMaxHealth(int mHealth);
	void setCurrentHealth(int cHealth);
};