#ifndef GAME_CANNON_HEADER_INCLUDED
#define GAME_CANNON_HEADER_INCLUDED

namespace game
{
	enum class cannonWeight
	{
		LIGHT,
		MEDIUM,
		HEAVY,
	};

	class Cannon
	{
		cannonWeight weight;

	};
}

#endif