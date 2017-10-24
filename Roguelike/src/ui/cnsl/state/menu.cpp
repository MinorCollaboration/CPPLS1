#include "menu.h"

#include <utils/array.hpp>

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
	std::cout << "Menu" << std::endl;
	
	utils::Array<int> myArray;

	myArray.addItem(5);
	myArray.addItem(6);

	std::cout << "the numbers" << std::endl;
	for (auto elem : myArray)
	{
		std::cout << elem << std::endl;
	}
}

void Menu::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription newGameComandDescription;
	newGameComandDescription.command = "NewGame";
	newGameComandDescription.description = "Start a new game.";

	commandDescriptionsBuffer.emplace_back(std::move(newGameComandDescription));
}
