#include "harbor.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Harbor::TYPE(Type::HARBOR);

void Harbor::BuyCommandHandler(utils::cmd::Command& command)
{
	utils::CharString name = command.GetParameter<utils::CharString>(0);

	for (auto ship : context.game.currentPort.buyableShips)
	{
		char* shipName = &utils::chartolower(ship->type);
		if (std::strcmp(name, shipName) == 0)
		{
			if (context.game.ExchangeShip(*ship)) {
				context.userInterface.DrawConsole("You changed your ship");
			}
			else {
				context.userInterface.DrawConsole("You could not afford that ship");
			}
			
			delete[] shipName;
			delete[] name.str;
			return;
		}

		delete[] shipName;
	}

	context.userInterface.DrawConsole("Could not find the ship you wanted");
	delete[] name.str;
}

void Harbor::Initialize()
{
	context.userInterface.RegisterCommand<utils::CharString>("Buy", std::bind(&Harbor::BuyCommandHandler, this, std::placeholders::_1));
}

void Harbor::Terminate()
{
	context.userInterface.UnregisterCommand("Buy");
}

void Harbor::DrawConsole() const
{
	auto ship		= &context.game.currentShip;

	int damage		= ship->maxLifePoints - ship->lifePoints;
	int repairCost  = damage * 10;

	int returnRate	= (ship->price - repairCost) / 2;
	int availGold	= context.game.Gold() + returnRate;

	std::cout << "You're at the harbor, here you can exchange your ship for a new one." << std::endl;
	std::cout << "Your ships will be sold for half it's value, it's value is calculated on the origin price minus cost to repair" << std::endl;
	std::cout << "You can spend a total of " << availGold << " for your new ship" << std::endl << std::endl;

	std::cout << "your current ship it the " << ship->type << " it has room for " << ship->loadSize << " items"
		<< " and " << ship->cannonSize << " cannons" << std::endl;

	switch (ship->size)
	{
	case game::shipSize::klein: std::cout << "Your ship is a small one. "; break;
	case game::shipSize::normaal: std::cout << "Your ship is from a normal size. "; break;
	}

	switch (ship->weight)
	{
	case game::shipWeight::licht: std::cout << "it's weight is kinda low." << std::endl << std::endl; break;
	case game::shipWeight::normaal: std::cout << "it's weight is pretty average." << std::endl << std::endl; break;
	case game::shipWeight::log: std::cout << "it's weight is very heavy." << std::endl << std::endl; break;
	}

	std::cout << "You're now carrying " << ship->cannons.size() << " cannons" << std::endl << std::endl;

	std::cout << "These ships are available for sale" << std::endl;
	std::cout << "Type:			" << "Price:	" << "Cannons:	" << "LoadSize:	" << "Lifepoints:	" << "Size:		" << "Weight:	"<< std::endl;
	for (auto ship : context.game.currentPort.buyableShips)
	{
		int strlen = std::strlen(ship->type);

		std::cout << ship->type << ",	" << (strlen < 15 ? "	" : "") << (strlen < 7 ? "	" : "")
			<< ship->price << ",	" << ship->cannonSize << ",		"
			<< ship->loadSize << ",		" << ship->maxLifePoints << "		"
			<< (ship->size == game::shipSize::klein ? "Small		" : "Normal		")
			<< (ship->weight == game::shipWeight::log ? "Log" : (ship->weight == game::shipWeight::licht ? "Licht" : "Normal"))
			<< std::endl;
	}

	std::cout << "Which one will it be?";
}

void Harbor::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription buyCommandDescription;
	buyCommandDescription.command = "Buy";
	buyCommandDescription.description = "Buy a new cannon";
	buyCommandDescription.parameters.addItem("type");

	commandDescriptionsBuffer.addItem(buyCommandDescription);
}