#ifndef GAME_PORT_HEADER_INCLUDED
#define GAME_PORT_HEADER_INCLUDED

#include <utils/array.hpp>

#include <system_error>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "errorcategory.h"

#include "ship.h"

namespace game
{
	class Port;
	class Ship;
	class Item;

	typedef utils::Array<Port*> PortsContainer;
	typedef utils::Array<Ship*> ShipsContainer;
	typedef utils::Array<Item*> ItemsContainer;

	class Port
	{
	private:
	public:
		ShipsContainer buyableShips;
		ItemsContainer buyableItems;
		ItemsContainer sellableItems;

		char* name;

		void EnterPort(ShipsContainer);
		void LeavePort();
	};

	PortsContainer ParsePorts(std::istream& stream);
	PortsContainer ParsePorts(std::istream& stream, std::error_code& errorBuffer);

	PortsContainer GetAvailablePorts();

	int			   ParsePortDis(std::istream& stream, Port, Port);
	int			   ParsePortDis(std::istream& stream, Port, Port, std::error_code& errorBuffer);
	int			   GetPortDistance(Port, Port);
}

#endif