#include "port.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace game;
using namespace std;

namespace
{
	char const* PORT_FILES_FOLDER = "./";
	char const* PORT_FILE_EXTENSION = ".csv";
}

PortsContainer game::ParsePort(std::istream& stream)
{
	PortsContainer ports;

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

	char* portFilePath;
	strcpy_s(portFilePath, PORT_FILES_FOLDER);
	strcat_s(portFilePath, "/ports");
	strcas_s(portFilePath, PORT_FILE_EXTENSION);
	std::ifstream stream(portFilePath);

	std::error_code errorBuffer;
	ports = ParsePort(stream, errorBuffer);
	if (errorBuffer)
		return PortsContainer();

	return ports;
}
