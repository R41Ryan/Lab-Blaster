#include <weaponStats.h>

WeaponStats::WeaponStats()
{
	setPistol();
	/*
	setShotgun();
	setSMG();
	setSniper();
	setMachineGun();
	
	setFists();
	setKnife();
	setBaseballBat();
	setSword();
	setChainsaw();
	*/
}

int WeaponStats::getGunDamage(int weapon)
{
	return gunDamage[weapon];
}

double WeaponStats::getGunAngle(int weapon)
{
	return gunAccuracyConeAngle[weapon];
}

int WeaponStats::getGunPrice(int weapon)
{
	return gunPrice[weapon];
}

int WeaponStats::getMeleeDamage(int weapon)
{
	return meleeDamage[weapon];
}

double WeaponStats::getMeleeAngle(int weapon)
{
	return meleeConeOfEffectAngle[weapon];
}

int WeaponStats::getMeleeRange(int weapon)
{
	return meleeRange[weapon];
}

int WeaponStats::getMeleePrice(int weapon)
{
	return meleePrice[weapon];
}

void WeaponStats::setPistol()
{
	gunDamage[PISTOL] = 50;
	gunAccuracyConeAngle[PISTOL] = 10;
	gunPrice[PISTOL] = 0;
}