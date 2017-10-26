#include "cannon.h"

using namespace game;

int Cannon::Shoot()
{
	return utils::random(minDamage, maxDamage);
}

CannonContainer game::GetAvailableCannons()
{
	CannonContainer cannonContainer;

	Cannon* lightCannon = new Cannon();
	lightCannon->weight = cannonWeight::LIGHT;
	lightCannon->minDamage = 0;
	lightCannon->maxDamage = 2;
	lightCannon->price = 50;

	Cannon* mediumCannon = new Cannon();
	mediumCannon->weight = cannonWeight::MEDIUM;
	mediumCannon->minDamage = 0;
	mediumCannon->maxDamage = 4;
	mediumCannon->price = 200;

	Cannon* heavyCannon = new Cannon();
	heavyCannon->weight = cannonWeight::HEAVY;
	heavyCannon->minDamage = 0;
	heavyCannon->maxDamage = 6;
	heavyCannon->price = 1000;

	cannonContainer.addItem(lightCannon);
	cannonContainer.addItem(mediumCannon);
	cannonContainer.addItem(heavyCannon);

	return cannonContainer;
}