#include "newgame.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Newgame::TYPE(Type::NEWGAME);

void Newgame::Initialize()
{
	context.game.Start();

	context.userInterface.RegisterCommand<>("Continue", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::PORT); });
}

void Newgame::Terminate()
{
	context.userInterface.UnregisterCommand("Continue");
}

void Newgame::DrawConsole() const
{
	std::cout << "You've being spawned at " << context.game.currentPort.name << std::endl << std::endl;

	std::cout << "Your ship is the " << context.game.currentShip.type << std::endl;
	std::cout << "It has room for " << context.game.currentShip.cannonSize << " cannons" << std::endl;
	
	int cannonCount = 0;
	for (auto cannon : context.game.currentShip.cannons) cannonCount += cannon->amount;
	std::cout << cannonCount << " cannons have already be added as a gift" << std::endl;
	std::cout << "Your ship is able to take " << context.game.currentShip.maxLifePoints << " damage" << std::endl;

	std::cout << "You also have being assigned " << context.game.Gold() << " gold to use during your journey" << std::endl;
	std::cout << "What will your first action be during this adventure" << std::endl;
}

void Newgame::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription continueCommandDescription;
	continueCommandDescription.command = "Continue";
	continueCommandDescription.description = "Get to the port to decide your next action";

	commandDescriptionsBuffer.addItem(continueCommandDescription);
}
