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
	std::cout << "and it can take " << context.game.currentShip.maxLifePoints << " damage" << std::endl;

	std::cout << "You also have being assigned " << context.game.Gold() << " gold to use during your journey" << std::endl;
	std::cout << "What will your first action be during this adventure" << std::endl;
}

void newgame::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	/*CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));*/
}
