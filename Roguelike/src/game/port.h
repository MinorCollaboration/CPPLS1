#ifndef GAME_PORT_HEADER_INCLUDED
#define GAME_PORT_HEADER_INCLUDED

#include <array>
#include <system_error>
#include <string>			// only used for std::getline() to process file lines;
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "errorcategory.h"

#include "ship.h"

namespace game
{
	class Port;

	typedef std::array<Port*, 24> PortsContainer; // Currently available ports

	class Port
	{
	private:
	public:
		std::array<Ship*, 13> availableShips;
		char* name;

	};

	PortsContainer ParsePort(std::istream& stream);
	PortsContainer ParsePort(std::istream& stream, std::error_code& errorBuffer);

	PortsContainer GetAvailablePorts();
}

#endif