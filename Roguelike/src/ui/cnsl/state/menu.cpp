#include "menu.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Menu::TYPE(Type::MENU);

void Menu::Initialize()
{
	// Register commands.
	context.userInterface.RegisterCommand<>("NewGame", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::NEWGAME); });
}

void Menu::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("NewGame");
}

void Menu::DrawConsole() const
{
	std::cout << "Menu";
}

void Menu::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription newGameComandDescription;
	newGameComandDescription.command = "NewGame";
	newGameComandDescription.description = "Start a new game.";

	commandDescriptionsBuffer.addItem(std::move(newGameComandDescription));
}
