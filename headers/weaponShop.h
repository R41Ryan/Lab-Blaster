#pragma once
#include "../headers/weaponStats.h"
#include <SDL_render.h>

class WeaponShop
{
private:
	int tab;
	bool gunPurchased[TOTAL_GUN_TYPES];
	bool meleePurchased[TOTAL_MELEE_TYPES];
public:
	// Constructors

	WeaponShop();

	// Functions

	// Purchases the item in the gun tab (tab 0) as indicated by the gun parameter by setting its gunPurchased index to true;
	// Returns true if the item in question had not been purchased yet. Returns false otherwise.
	bool purchaseGun(int gun);

	// Purchases the item in the melee tab (tab 1) as indicated by the melee parameter by setting its meleePurchased index to true;
	// Returns true if the item in question had not been purchased yet. Returns false otherwise.
	bool purchaseMelee(int melee);

	// Changes the currently displayed tab to either 0 or 1 depending on the parameter given.
	void switchTab(int t);

	// Resets all purchase statuses to false, allowing all items to be buyable again.
	void resetPurchases();

	// Getters

	// Setters
};