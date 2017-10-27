#include "harbor.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Harbor::TYPE(Type::HARBOR);

void Harbor::BuyCommandHandler(utils::cmd::Command& command)
{
	context.userInterface.Exit();
}

void Harbor::Initialize()
{
}

void Harbor::Terminate()
{
}

void Harbor::DrawConsole() const
{
	auto ship		= context.game.currentShip;

	int damage		= ship.maxLifePoints - ship.lifePoints;
	int repairCost  = damage * 10;

	int returnRate	= (ship.price - repairCost) / 2;
	int availGold	= context.game.Gold() + returnRate;

	std::cout << "You're at the harbor, here you can exchange your ship for a new one." << std::endl;
	std::cout << "Your ships will be sold for half it's value, it's value is calculated on the origin price minus cost to repair" << std::endl;
	std::cout << "You can spend a total of " << availGold << " for your new ship" << std::endl << std::endl;

	std::cout << "these are available for sale" << std::endl;
	std::cout << "Type:			" << "Price:	" << "Cannons:	" << "LoadSize:	" << "Lifepoints:	" << "Size:		" << "Weight:	"<< std::endl;
	for (auto ship : context.game.ships)
	{
		if (utils::random(1) == 1) {
			int strlen = std::strlen(ship->type);

			std::cout << ship->type << ",	" << (strlen < 15 ? "	" : "") << (strlen < 7 ? "	" : "")
				<< ship->price << ",	" << ship->cannonSize << ",		"
				<< ship->loadSize << ",		" << ship->maxLifePoints << "		"
				<< (ship->size == game::shipSize::klein ? "Small		" : "Normal		")
				<< (ship->weight == game::shipWeight::log ? "Log" : (ship->weight == game::shipWeight::licht ? "Licht" : "Normal"))
				<< std::endl;
		}
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