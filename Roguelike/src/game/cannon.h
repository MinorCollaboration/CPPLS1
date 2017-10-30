#ifndef GAME_CANNON_HEADER_INCLUDED
#define GAME_CANNON_HEADER_INCLUDED

#include <utils/array.hpp>
#include <utils/int.hpp>

namespace game
{
	class Cannon;

	typedef utils::Array<Cannon*> CannonContainer;

	enum class cannonWeight
	{
		LIGHT,
		MEDIUM,
		HEAVY,
	};

	class Cannon
	{
	public:
		int amount = 1;

		int price;
		int minDamage;
		int maxDamage;
		cannonWeight weight;

		int Shoot();
	};

	CannonContainer GetAvailableCannons();
}

#endif