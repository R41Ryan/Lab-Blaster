#include <weaponStats.h>

WeaponStats::WeaponStats()
{
	setPistol();
	setShotgun();
	setSMG();
	setSniper();
	setMachineGun();
	
	setFists();
	setKnife();
	setBaseballBat();
	setSword();
	setChainsaw();
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

int WeaponStats::getGunPelletNum(int weapon)
{
	return gunPelletNum[weapon];
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
	gunKnockback[PISTOL] = 10;
	gunFireRate[PISTOL] = 3;
	gunPelletNum[PISTOL] = 1;
}

void WeaponStats::setShotgun()
{
	gunDamage[SHOTGUN] = 40;
	gunAccuracyConeAngle[SHOTGUN] = 30;
	gunPrice[SHOTGUN] = 400;
	gunKnockback[SHOTGUN] = 50;
	gunFireRate[SHOTGUN] = 1;
	gunPelletNum[SHOTGUN] = 8;
}

void WeaponStats::setSMG()
{
	gunDamage[SMG] = 40;
	gunAccuracyConeAngle[SMG] = 15;
	gunPrice[SMG] = 750;
	gunKnockback[SMG] = 1;
	gunFireRate[SMG] = 13;
	gunPelletNum[SMG] = 1;
}

void WeaponStats::setSniper()
{
	gunDamage[SNIPER] = 100;
	gunAccuracyConeAngle[SNIPER] = 1;
	gunPrice[SNIPER] = 1500;
	gunKnockback[SNIPER] = 50;
	gunFireRate[SNIPER] = 1;
	gunPelletNum[SNIPER] = 1;
}

void WeaponStats::setMachineGun()
{
	gunDamage[MACHINE_GUN] = 20;
	gunAccuracyConeAngle[MACHINE_GUN] = 20;
	gunPrice[MACHINE_GUN] = 2500;
	gunKnockback[MACHINE_GUN] = 5;
	gunFireRate[MACHINE_GUN] = 15;
	gunPelletNum[MACHINE_GUN] = 2;
}

void WeaponStats::setFists()
{
	meleeDamage[FISTS] = 40;
	meleeConeOfEffectAngle[FISTS] = 60;
	meleeRange[FISTS] = 50;
	meleePrice[FISTS] = 0;
	meleeKnockback[FISTS] = 35;
	meleeSwingRate[FISTS] = 2;
}

void WeaponStats::setKnife()
{
	meleeDamage[KNIFE] = 50;
	meleeConeOfEffectAngle[KNIFE] = 25;
	meleeRange[KNIFE] = 100;
	meleePrice[KNIFE] = 500;
	meleeKnockback[KNIFE] = 25;
	meleeSwingRate[KNIFE] = 4;
}

void WeaponStats::setBaseballBat()
{
	meleeDamage[BASEBALL_BAT] = 100;
	meleeConeOfEffectAngle[BASEBALL_BAT] = 90;
	meleeRange[BASEBALL_BAT] = 100;
	meleePrice[BASEBALL_BAT] = 1100;
	meleeKnockback[BASEBALL_BAT] = 50;
	meleeSwingRate[BASEBALL_BAT] = 2;
}

void WeaponStats::setSword()
{
	meleeDamage[SWORD] = 125;
	meleeConeOfEffectAngle[SWORD] = 90;
	meleeRange[SWORD] = 125;
	meleePrice[SWORD] = 1500;
	meleeKnockback[SWORD] = 50;
	meleeSwingRate[SWORD] = 4;
}

void WeaponStats::setChainsaw()
{
	meleeDamage[CHAINSAW] = 20;
	meleeConeOfEffectAngle[CHAINSAW] = 30;
	meleeRange[CHAINSAW] = 75;
	meleePrice[CHAINSAW] = 2000;
	meleeKnockback[CHAINSAW] = 10;
	meleeSwingRate[CHAINSAW] = 15;
}
