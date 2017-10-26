#include "newgame.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type newgame::TYPE(Type::NEWGAME);

void newgame::Initialize()
{
	context.game.Start();

	//context.userInterface.NewGame();
	//context.userInterface.RegisterCommand("Save", std::bind(&Gameover::SaveCommandHandler, this, std::placeholders::_1));
	//context.userInterface.UnregisterCommand("Back");
}

void newgame::Terminate()
{
	//context.userInterface.UnregisterCommand("Save");
}

void newgame::DrawConsole() const
{
	std::cout << "You've being spawned at " << context.game.currentPort.name << std::endl << std::endl;

	std::cout << "Your ship is the " << context.game.currentShip.type << std::endl;
	std::cout << "It has room for " << context.game.currentShip.cannonSize << " cannons" << std::endl;
	std::cout << context.game.currentShip.cannons.size() << " cannons have already be added as a gift" << std::endl;
	std::cout << "Your ship is able to take " << context.game.currentShip.maxLifePoints << " damage" << std::endl;

	std::cout << "You also have being assigned " << context.game.Gold() << " gold to use during your journey" << std::endl;
	std::cout << "What will your first action be during this adventure" << std::endl;
}

void newgame::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription shopCommandDescription;
	shopCommandDescription.command = "Shop";
	shopCommandDescription.description = "Go to the shop to by items";

	CommandDescription smithCommandDescription;
	smithCommandDescription.command = "Smith";
	smithCommandDescription.description = "Get to the ship to buy or sell cannons";

	CommandDescription harborCommandDescription;
	harborCommandDescription.command = "Harbor";
	harborCommandDescription.description = "Exchange your ship for a new ship";

	CommandDescription sailCommandDescription;
	sailCommandDescription.command = "Sail";
	sailCommandDescription.description = "Set sail to the next port";
	sailCommandDescription.parameters.addItem("port name");

	CommandDescription repairCommandDescription;
	repairCommandDescription.command = "Repair";
	repairCommandDescription.description = "Repair you ship for 10 gold pieces for each lifepoint";
	repairCommandDescription.parameters.addItem(":limit");

	commandDescriptionsBuffer.addItem(shopCommandDescription);
	commandDescriptionsBuffer.addItem(smithCommandDescription);
	commandDescriptionsBuffer.addItem(harborCommandDescription);
	commandDescriptionsBuffer.addItem(sailCommandDescription);
	commandDescriptionsBuffer.addItem(repairCommandDescription);
}
