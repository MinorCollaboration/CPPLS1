#ifndef GAME_PORT_HEADER_INCLUDED
#define GAME_PORT_HEADER_INCLUDED

#include <utils/array.hpp>
#include <system_error>
//#include <string>			// only used for std::getline() to process file lines;
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "errorcategory.h"

#include "ship.h"

namespace game
{
	class Port;

	typedef utils::Array<Port*> PortsContainer;

	class Port
	{
	private:
	public:
		~Port();

		//utils::Array<Ship*> availableShips;
		char* name;
	};

	PortsContainer ParsePort(std::istream& stream);
	PortsContainer ParsePort(std::istream& stream, std::error_code& errorBuffer);

	PortsContainer GetAvailablePorts();
}

#endif