#ifndef GAME_PORT_HEADER_INCLUDED
#define GAME_PORT_HEADER_INCLUDED

#include <array>
#include <system_error>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

#include <boost/filesystem.hpp>

#include "ship.h"

namespace game
{
	class Port;

	typedef std::array<Port*, 24> PortsContainer; // Currently available ports

	class Port
	{
	private:
		std::array<Ship, 13> availableShips;
	public:

	};

	PortsContainer ParsePort(std::istream& stream);
	PortsContainer ParsePort(std::istream& stream, std::error_code& errorBuffer);

	PortsContainer GetAvailablePorts();
}

#endif