#include "ship.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace game;

bool Ship::AddCannon(Cannon* cannon)
{
	if (cannons.size() < cannonSize) {
		if (!(size == shipSize::klein && cannon->weight == cannonWeight::HEAVY)) {
			cannons.addItem(cannon);
			return true;
		}

		return false;
	}

	return false;
}

bool Ship::RemoveCannon(cannonWeight cw)
{
	int i = 0;
	for (auto cannon : cannons)
	{
		try {
			if (cannon)
			{
				if (cannon->weight == cw) {
					delete cannons[i];
					cannons[i] = nullptr;
					return true;
				}
				else
				{
					cannons.pop_back();
				}
			}
		}
		catch (...)
		{
			cannons.pop_back();
		}
		
		i++;
	}
	return false;
}

bool Ship::AddItem(Item& toAdd)
{
	Item* clone = new Item(toAdd);
	if (items.size() < loadSize) {
		int i = 0;
		for (auto item : items)
		{
			if (std::strcmp(item->name, clone->name) == 0)
			{
				items[i]->amount += 1;
				delete[] clone;
				return true;
			}
			i++;
		}
		clone->amount = 1;
		items.addItem(clone);
		return true;
	}

	return false;
}

bool Ship::RemoveItem(Item toRemove)
{
	for (auto item : items) {
		if (std::strcmp(item->name, toRemove.name) == 0 && item->amount > 0) {
			item->amount -= 1;
			return true;
		}
	}

	return false;
}

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

				int strcmp = std::strcmp(extras, "klein,licht");

				if (std::strcmp(extras, "klein, licht") == 0 || std::strcmp(extras, "klein,licht") == 0) {
					ship->size		= shipSize::klein;
					ship->weight	= shipWeight::licht;
				} else if (std::strcmp(extras, "klein") == 0)
					ship->size		= shipSize::klein;
				else if (std::strcmp(extras,"licht") == 0)
					ship->weight	= shipWeight::licht;
				else if (std::strcmp(extras, "log") == 0)
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