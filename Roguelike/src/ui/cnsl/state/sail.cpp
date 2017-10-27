#include "sail.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Sail::TYPE(Type::SAIL);

void Sail::NextCommandHandler(utils::cmd::Command& command)
{
	context.userInterface.Exit();
}

void Sail::Initialize()
{
}

void Sail::Terminate()
{
}

void Sail::DrawConsole() const
{
	std::cout << "You're at the middle of the sea" << std::endl << std::endl;

	std::cout << "The wind is laying still and your sight is clear" << std::endl;
	std::cout << "What do you want to do?";
}

void Sail::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	/*CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));*/
}
