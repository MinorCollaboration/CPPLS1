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

	typedef utils::Array<Port*> PortsContainer;

	class Port
	{
	private:
	public:
		utils::Array<Ship*> availableShips;
		char* name;

		void EnterPort(ShipsContainer);
		void LeavePort();
	};

	PortsContainer ParsePort(std::istream& stream);
	PortsContainer ParsePort(std::istream& stream, std::error_code& errorBuffer);

	PortsContainer GetAvailablePorts();

	int			   ParsePortDis(std::istream& stream, Port, Port);
	int			   ParsePortDis(std::istream& stream, Port, Port, std::error_code& errorBuffer);
	int			   GetPortDistance(Port, Port);
}

#endif