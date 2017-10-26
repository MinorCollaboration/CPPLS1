#include "port.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace game;

PortsContainer game::ParsePort(std::istream& stream)
{
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);

	PortsContainer ports;

	bool passFirstRow = false;

	char* portLine = new char[1000];
	int i = 0;
	do
	{
		if (!stream || !stream.getline(portLine, 1000)) {
			delete[] portLine;
			throw std::system_error(Error::STREAM_ERROR);
		}

		if (stream.gcount() == 0 || portLine[0] == '\0' || portLine[0] == '\ ' || portLine == nullptr || portLine[0] == '#')
			continue;

		if (!passFirstRow) {
			std::stringstream ss(portLine);
			char* name = new char[100];
			while (ss.getline(name, 100, ';')) {
				if (name[0] == '\0') continue;

				Port* port = new Port();
				port->name = name;
				ports.addItem(port);

				name = new char[100];
			}
			delete name;
			passFirstRow = true;
		} else {
			// Distances parsing
			i++;
		}
		
		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);
	} while (!stream.eof());

	delete[] portLine;

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
		return PortsContainer();
	}
}

PortsContainer game::GetAvailablePorts()
{
	std::ifstream stream("./ports.csv");
	std::error_code errorBuffer;
	return ParsePort(stream, errorBuffer);
}
