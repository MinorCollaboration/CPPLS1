#include "ship.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace game;

ShipsContainer game::ParseShip(std::istream& stream)
{
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);

	ShipsContainer ships;

	bool passFirstRow = false;

	char* shipLine = new char[1000];
	int i = 0;
	do
	{
		if (!stream || !stream.getline(shipLine, 1000)) {
			delete[] shipLine;
			throw std::system_error(Error::STREAM_ERROR);
		}

		if (stream.gcount() == 0 || shipLine[0] == '\0' || shipLine == nullptr || shipLine[0] == '#')
			continue;

		if (!passFirstRow)
			passFirstRow = true;
		else {
			std::istringstream iss(shipLine);
			char* name			= new char[100];
			char* price			= new char[10];
			char* loadSize		= new char[10];
			char* cannonSize	= new char[10];
			char* maxLifePoints	= new char[10];
			char* extras		= new char[20];

			Ship* ship = new Ship();

			iss.getline(name, 100, ';');
			iss.getline(price, 10, ';');
			iss.getline(loadSize, 10, ';');
			iss.getline(cannonSize, 10, ';');
			iss.getline(maxLifePoints, 10, ';');
			iss.getline(extras, 20);

			ship->type			= name;
			ship->price			= atoi(price);
			ship->loadSize		= atoi(loadSize);
			ship->cannonSize	= atoi(cannonSize);
			ship->lifePoints	= atoi(maxLifePoints);
			ship->maxLifePoints	= atoi(maxLifePoints);

			if (extras) {
				if (extras == "klein, licht") {
					ship->size		= shipSize::klein;
					ship->weight	= shipWeight::licht;
				} else if (extras == "klein") 
					ship->size		= shipSize::klein;
				else if (extras == "licht")
					ship->weight	= shipWeight::licht;
				else if (extras == "log")
					ship->weight	= shipWeight::log;
			}

			ships.addItem(ship);

			delete price;
			delete loadSize;
			delete cannonSize;
			delete maxLifePoints;
			delete extras;
		}

		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);
	} while (!stream.eof());

	delete[] shipLine;

	return ships;
}

ShipsContainer game::ParseShip(std::istream& stream, std::error_code& errorBuffer)
{
	try
	{
		return ParseShip(stream);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return ShipsContainer();
	}
}

ShipsContainer game::GetAvailableShips()
{
	std::ifstream stream("./ships.csv");
	std::error_code errorBuffer;
	return ParseShip(stream, errorBuffer);
}