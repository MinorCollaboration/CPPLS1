#include "port.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace game;

PortsContainer game::ParsePort(std::istream& stream)
{
	PortsContainer ports;

	bool passFirstRow = false;

	std::string portLine;
	int i = 0;
	while (std::getline(stream, portLine))
	{
		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);

		if (portLine.empty() || portLine[0] == '#')
			continue;

		Port portje;

		portje.availableShips = {};

		std::string szportLine = portLine.substr(1, portLine.length() - 2);
		std::stringstream ss(szportLine);

		std::string name;

		if (!passFirstRow)
		{
			while (std::getline(ss, name, ';'))
			{
				Port port;
				char* portname = const_cast<char*>(name.c_str());
				port.name = portname;
				ports.addItem(&port);
			}

			passFirstRow = true;
		}
		else
		{
			Port port = *ports[i];
			i++;
		}
		

		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);

	}

	return ports;
}

PortsContainer game::ParsePort(std::istream& stream, std::error_code& errorBuffer)
{
	try
	{
		return ParsePort(stream);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

PortsContainer game::GetAvailablePorts()
{
	PortsContainer ports;

	std::ifstream stream("./ports.csv");

	std::error_code errorBuffer;
	ports = ParsePort(stream, errorBuffer);
	if (errorBuffer)
		return PortsContainer();

	return ports;
}
