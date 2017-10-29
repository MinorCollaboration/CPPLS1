#ifndef GAME_ITEM_HEADER_INCLUDED
#define GAME_ITEM_HEADER_INCLUDED

#include <utils/array.hpp>

#include <system_error>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "errorcategory.h"

#include "port.h"

namespace game
{
	class Item;
	class Port;

	typedef utils::Array<Item*> ItemsContainer;

	class Item
	{
	private:
	public:
		char*		name;
		int			amount;
		int			price;
	};
	
	ItemsContainer	ParseItems(std::istream& stream);
	ItemsContainer	ParseItems(std::istream& stream, std::error_code& errorBuffer);

	ItemsContainer	GetAvailableItems();

	int				GetItemMinAmount(std::istream& stream, Item, Port);
	int				GetItemMinAmount(std::istream& stream, Item, Port, std::error_code& errorBuffer);
	int				GetItemMinAmount(Item, Port);
	   				
	int				GetItemMaxAmount(std::istream& stream, Item, Port);
	int				GetItemMaxAmount(std::istream& stream, Item, Port, std::error_code& errorBuffer);
	int				GetItemMaxAmount(Item, Port);
	   				
	int				GetItemMinPrice(std::istream& stream, Item, Port);
	int				GetItemMinPrice(std::istream& stream, Item, Port, std::error_code& errorBuffer);
	int				GetItemMinPrice(Item, Port);
	   				
	int				GetItemMaxPrice(std::istream& stream, Item, Port);
	int				GetItemMaxPrice(std::istream& stream, Item, Port, std::error_code& errorBuffer);
	int				GetItemMaxPrice(Item, Port);
}

#endif