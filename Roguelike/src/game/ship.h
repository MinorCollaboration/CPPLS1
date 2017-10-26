#ifndef GAME_SHIP_HEADER_INCLUDED
#define GAME_SHIP_HEADER_INCLUDED

#include <utils/array.hpp>
#include <system_error>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "errorcategory.h"

namespace game
{
	class Ship;

	typedef utils::Array<Ship*> ShipsContainer;

	enum class shipSize
	{
		klein,
		normaal
		//groot
	};

	enum class shipWeight
	{
		licht,
		normaal,
		log,
	};

	class Ship
	{
	private:
	public:
		char*   type;
		int		price;
		int		loadSize;
		int		cannonSize;
		int		lifePoints;
		int		maxLifePoints;

		// Exceptionals
		shipSize	size	= shipSize::normaal; // klein/(:groot)
		shipWeight	weight	= shipWeight::normaal; // Licht/log
		
	};

	ShipsContainer ParseShip(std::istream& stream);
	ShipsContainer ParseShip(std::istream& stream, std::error_code& errorBuffer);

	ShipsContainer GetAvailableShips();
}

#endif