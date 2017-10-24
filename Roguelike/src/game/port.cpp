#include "port.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace game;

PortsContainer game::ParsePort(std::istream& stream)
{
	PortsContainer ports;

	std::string portLine;
	while (std::getline(stream, portLine))
	{
		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);

		if (portLine.empty() || portLine[0] == '#')
			continue;

		Port portje;

		portje.name = "hoi";
		portje.availableShips = {};

		std::string szportLine = portLine.substr(1, portLine.length() - 2);
		std::stringstream ss(szportLine);

		std::string name;

		std::getline(ss, name, ';');
		char* portname = const_cast<char*>(name.c_str());
		portje.name = portname;

		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);

		ports.addItem(&portje);
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
