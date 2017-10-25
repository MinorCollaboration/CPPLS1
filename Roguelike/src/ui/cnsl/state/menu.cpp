#include "menu.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Menu::TYPE(Type::MENU);

void Menu::Initialize()
{
	// Register commands.
	context.userInterface.RegisterCommand<>("NewGame", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::GAMEOVER); });
}

void Menu::Terminate()
{
	// Unregister commands.
	context.userInterface.UnregisterCommand("NewGame");
}

void Menu::DrawConsole() const
{
	std::cout << "Menu" << std::endl << std::endl;

	std::cout << "Beschikbare havens" << std::endl;

	for (auto* port : context.game.ports)
	{
		port->name[100] = '\0';
		std::cout << port->name  << std::endl;
	}
}

void Menu::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription newGameComandDescription;
	newGameComandDescription.command = "NewGame";
	newGameComandDescription.description = "Start a new game.";

	commandDescriptionsBuffer.addItem(std::move(newGameComandDescription));
}
