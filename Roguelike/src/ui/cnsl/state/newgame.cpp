#include "newgame.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type newgame::TYPE(Type::NEWGAME);

void newgame::Initialize()
{
	context.userInterface.NewGame();
	//context.userInterface.RegisterCommand("Save", std::bind(&Gameover::SaveCommandHandler, this, std::placeholders::_1));
	//context.userInterface.UnregisterCommand("Back");
}

void newgame::Terminate()
{
	//context.userInterface.UnregisterCommand("Save");
}

void newgame::DrawConsole() const
{
	std::cout << std::endl << "Newgame" << std::endl << std::endl << "Starting new game" << std::endl;
}

void newgame::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	/*CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));*/
}
