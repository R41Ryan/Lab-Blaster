#include <weaponStats.h>

WeaponStats::WeaponStats()
{
	setPistol();
	/*
	setShotgun();
	setSMG();
	setSniper();
	setMachineGun();
	*/
	
	setFists();
	/*
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

int WeaponStats::getGunKnockback(int weapon)
{
	return gunKnockback[weapon];
}

int WeaponStats::getGunFireRate(int weapon)
{
	return gunFireRate[weapon];
}

int WeaponStats::getMeleeDamage(int weapon)
{
	return meleeDamage[weapon];
}

double WeaponStats::getMeleeAngle(int weapon)
{
	return meleeConeOfEffectAngle[weapon];
}

float WeaponStats::getMeleeRange(int weapon)
{
	return meleeRange[weapon];
}

int WeaponStats::getMeleePrice(int weapon)
{
	return meleePrice[weapon];
}

float WeaponStats::getMeleeKnockback(int weapon)
{
	return meleeKnockback[weapon];
}

float WeaponStats::getMeleeSwingRate(int weapon)
{
	return meleeSwingRate[weapon];
}

void WeaponStats::setPistol()
{
	gunDamage[PISTOL] = 50;
	gunAccuracyConeAngle[PISTOL] = 5;
	gunPrice[PISTOL] = 0;
	gunKnockback[PISTOL] = 1;
	gunFireRate[PISTOL] = 3;
}

void WeaponStats::setFists()
{
	meleeDamage[FISTS] = 25;
	meleeConeOfEffectAngle[FISTS] = 60;
	meleeRange[FISTS] = 50;
	meleePrice[FISTS] = 0;
	meleeKnockback[FISTS] = 35;
	meleeSwingRate[FISTS] = 2;
}