#pragma once

enum gunTypes
{
	PISTOL,
	SHOTGUN,
	SMG,
	SNIPER,
	MACHINE_GUN,
	TOTAL_GUN_TYPES
};

enum gunStates
{
	GUN_IDLE,
	GUN_FIRING,
	TOTAL_GUN_STATES
};

enum meleeTypes
{
	FISTS,
	KNIFE,
	BASEBALL_BAT,
	SWORD,
	CHAINSAW,
	TOTAL_MELEE_TYPES
};

class WeaponStats 
{
private:
	int gunDamage[TOTAL_GUN_TYPES];
	double gunAccuracyConeAngle[TOTAL_GUN_TYPES];
	int gunPrice[TOTAL_GUN_TYPES];
	int gunKnockback[TOTAL_GUN_TYPES];
	int gunFireRate[TOTAL_GUN_TYPES];
	int gunPelletNum[TOTAL_GUN_TYPES];

	int meleeDamage[TOTAL_MELEE_TYPES];
	double meleeConeOfEffectAngle[TOTAL_MELEE_TYPES];
	float meleeRange[TOTAL_MELEE_TYPES];
	int meleePrice[TOTAL_MELEE_TYPES];
	float meleeKnockback[TOTAL_MELEE_TYPES];
	float meleeSwingRate[TOTAL_MELEE_TYPES];

public:
	// Constructor

	WeaponStats();
	// Get the damage of the specified gun type.
	int getGunDamage(int weapon);
	// Get the angle of the accuracy cone of the specified gun type in degrees.
	double getGunAngle(int weapon);
	// Get the price of the specified gun type.
	int getGunPrice(int weapon);
	// Get the knockback power of the specified gun type in the number of pixels the target would be knocked back by.
	int getGunKnockback(int weapon);
	// Get the fire rate of the specified gun type in rounds per second.
	int getGunFireRate(int weapon);
	// Get the number of pellets per shot of the specified gun.
	int getGunPelletNum(int weapon);
	// Get the damage of the specified melee type.
	int getMeleeDamage(int weapon);
	// Get the angle of the cone of effect for the specified melee type in degrees.
	double getMeleeAngle(int weapon);
	// Get the range of the cone of effect for the specified melee type in pixels.
	float getMeleeRange(int weapon);
	// Get the price of the specified melee type.
	int getMeleePrice(int weapon);
	// Get the knockback power of the specified melee type in the number of pixels the target would be knocked back by.
	float getMeleeKnockback(int weapon);
	// Get the swing rate of the specified melee type in swings per second;
	float getMeleeSwingRate(int weapon);

	// Sets the stats for the pistol;
	void setPistol();
	// Sets the stats for the shotgun;
	void setShotgun();
	// Sets the stats for the SMG;
	void setSMG();
	// Sets the stats for the sniper;
	void setSniper();
	// Sets the stats for the machine gun;
	void setMachineGun();
	
	// Sets the stats for the fists;
	void setFists();
	// Sets the stats for the knife;
	void setKnife();
	// Sets the stats for the baseball bat;
	void setBaseballBat();
	// Sets the stats for the sword;
	void setSword();
	// Sets the stats for the chainsaw;
	void setChainsaw();
};