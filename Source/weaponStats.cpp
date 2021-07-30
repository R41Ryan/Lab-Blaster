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

int WeaponStats::getMeleeRange(int weapon)
{
	return meleeRange[weapon];
}

int WeaponStats::getMeleePrice(int weapon)
{
	return meleePrice[weapon];
}

int WeaponStats::getMeleeKnockback(int weapon)
{
	return meleeKnockback[weapon];
}

int WeaponStats::getMeleeSwingRate(int weapon)
{
	return meleeSwingRate[weapon];
}

void WeaponStats::setPistol()
{
	gunDamage[PISTOL] = 50;
	gunAccuracyConeAngle[PISTOL] = 10;
	gunPrice[PISTOL] = 0;
	gunKnockback[PISTOL] = 0;
	gunFireRate[PISTOL] = 4;
}

void WeaponStats::setFists()
{
	meleeDamage[FISTS] = 50;
	meleeConeOfEffectAngle[FISTS] = 30;
	meleeRange[FISTS] = 30;
	meleePrice[FISTS] = 0;
	meleeKnockback[FISTS] = 5;
}