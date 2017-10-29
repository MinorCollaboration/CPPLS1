#include "item.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace game;

ItemsContainer game::ParseItems(std::istream& stream)
{
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);

	ItemsContainer items;

	bool passFirstRow = false;

	char* itemLine = new char[1000];
	int i = 0;
	do
	{
		if (!stream || !stream.getline(itemLine, 1000)) {
			delete[] itemLine;
			throw std::system_error(Error::STREAM_ERROR);
		}

		if (stream.gcount() == 0 || itemLine[0] == '\0' || itemLine[0] == '\ ' || itemLine == nullptr || itemLine[0] == '#')
			continue;

		if (!passFirstRow) {
			std::stringstream ss(itemLine);
			char* name = new char[100];
			while (ss.getline(name, 100, ';')) {
				if (name[0] == '\0') continue;

				Item* item = new Item();
				item->name = name;
				items.addItem(item);

				name = new char[100];
			}
			delete[] name;
			passFirstRow = true; // First do the stream check before breaking out
		}
		else {
			break;
		}

		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);
	} while (!stream.eof());

	delete[] itemLine;

	return items;
}

ItemsContainer game::ParseItems(std::istream& stream, std::error_code& errorBuffer)
{
	try
	{
		return ParseItems(stream);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return ItemsContainer();
	}
}

ItemsContainer game::GetAvailableItems()
{
	std::ifstream stream("./itemPrice.csv"); // Could also be itemAmount but this one seems to have less chars to parse
	std::error_code errorBuffer;
	return ParseItems(stream, errorBuffer);
}

int	game::GetItemMinAmount(std::istream& stream, Item, Port)
{
	return -1;
}

int	game::GetItemMaxAmount(std::istream& stream, Item, Port)
{
	return -1;
}

int	game::GetItemMinPrice(std::istream& stream, Item, Port)
{
	return -1;
}

int	game::GetItemMaxPrice(std::istream& stream, Item, Port)
{
	return -1;
}

int	game::GetItemMinAmount(std::istream& stream, Item item, Port port, std::error_code& errorBuffer)
{
	try
	{
		return GetItemMinAmount(stream, item, port);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return 0;
	}
}

int	game::GetItemMaxAmount(std::istream& stream, Item item, Port port, std::error_code& errorBuffer)
{
	try
	{
		return GetItemMaxAmount(stream, item, port);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return 0;
	}
}

int	game::GetItemMinPrice(std::istream& stream, Item item, Port port, std::error_code& errorBuffer)
{
	try
	{
		return GetItemMinPrice(stream, item, port);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return 0;
	}
}

int	game::GetItemMaxPrice(std::istream& stream, Item item, Port port, std::error_code& errorBuffer)
{
	try
	{
		return GetItemMaxPrice(stream, item, port);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
		return 0;
	}
}

int game::GetItemMinAmount(Item item, Port port)
{
	std::ifstream stream("./itemAmount.csv");
	std::error_code errorBuffer;
	return GetItemMinAmount(stream, item, port, errorBuffer);
}

int game::GetItemMaxAmount(Item item, Port port)
{
	std::ifstream stream("./itemAmount.csv");
	std::error_code errorBuffer;
	return GetItemMaxAmount(stream, item, port, errorBuffer);
}

int game::GetItemMinPrice(Item item, Port port)
{
	std::ifstream stream("./itemPrice.csv");
	std::error_code errorBuffer;
	return GetItemMinPrice(stream, item, port, errorBuffer);
}

int game::GetItemMaxPrice(Item item, Port port)
{
	std::ifstream stream("./itemPrice.csv");
	std::error_code errorBuffer;
	return GetItemMaxPrice(stream, item, port, errorBuffer);
}