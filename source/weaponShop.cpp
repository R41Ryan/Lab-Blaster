#include "../headers/weaponShop.h"

WeaponShop::WeaponShop()
{
	tab = 0;
	resetPurchases();
}

bool WeaponShop::purchaseGun(int gun)
{
	if (gunPurchased[gun])
	{
		return false;
	}
	else
	{
		gunPurchased[gun] = true;
		return true;
	}
}

bool WeaponShop::purchaseMelee(int melee)
{
	if (meleePurchased[melee])
	{
		return false;
	}
	else
	{
		meleePurchased[melee] = true;
		return true;
	}
}

void WeaponShop::switchTab(int t)
{
	tab = t;
}

void WeaponShop::resetPurchases()
{
	for (int i = 0; i < TOTAL_GUN_TYPES; i++)
	{
		gunPurchased[i] = false;
	}
	for (int i = 0; i < TOTAL_MELEE_TYPES; i++)
	{
		meleePurchased[i] = false;
	}
}
