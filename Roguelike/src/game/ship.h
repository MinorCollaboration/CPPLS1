#ifndef GAME_SHIP_HEADER_INCLUDED
#define GAME_SHIP_HEADER_INCLUDED

namespace game
{
	enum class shipWeight
	{
		licht,
		log,
	};

	class Ship
	{
	private:
		char*	type const;
		int		price;
		int		loadSize;
		int		cannonSize;
		int		lifePoints;
		int		maxLifePoints;

		// Exceptionals
		char*		size;	// klein/(:groot)
		char*     weight = nullptr; // Licht/log
	public:
		
	};
}

#endif