#include "port.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace game;

void Port::EnterPort(ShipsContainer shipContainer)
{
	for (auto ship : shipContainer)
	{
		availableShips.addItem(ship);
	}
}

void Port::LeavePort()
{
	availableShips.clear();
}

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
			passFirstRow = true; // First do the stream check before breaking out
		} else {
			break;
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

int game::ParsePortDis(std::istream& stream, Port origin, Port destination)
{
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);


	char* portLine = new char[1000];
	int column = 0;
	bool passFirstRow = false;

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

				if (std::strcmp(name, origin.name) != 0)
					column++;
				else {
					passFirstRow;
					break;
				}

				delete[] name;
				name = new char[100];
			}
			
			delete[] name;
			passFirstRow = true; // First do the stream check before breaking out
		}
		else {
			std::stringstream ss(portLine);
			char* name = new char[100];

			ss.getline(name, 100, ';');
			if (std::strcmp(name, destination.name) == 0) {
				int columnsPassed = 0;
				char* distance = new char[5];
				while (ss.getline(distance, 5, ';')) {
					if (columnsPassed == column) {
						int returnValue = atoi(distance);

						delete[] name;
						delete[] distance;
						delete[] portLine;

						return returnValue;
					}
					else {
						columnsPassed++;
					}
				}

				delete[] distance;
			}

			delete[] name;
		}

		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);
	} while (!stream.eof());

	delete[] portLine;

	return 0;
}

int game::ParsePortDis(std::istream& stream, Port origin, Port destination, std::error_code& errorBuffer)
{
	try
	{
		return ParsePortDis(stream, origin, destination);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return 0;
	}
}

int game::GetPortDistance(Port origin, Port destination)
{
	std::ifstream stream("./ports.csv");
	std::error_code errorBuffer;
	return ParsePortDis(stream, origin, destination, errorBuffer);
}