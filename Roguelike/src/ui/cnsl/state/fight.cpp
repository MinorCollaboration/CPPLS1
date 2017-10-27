#include "fight.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Fight::TYPE(Type::FIGHT);

void Fight::ShootCommandHandler(utils::cmd::Command& command)
{
	context.userInterface.Exit();
}

void Fight::Initialize()
{
}

void Fight::Terminate()
{
}

void Fight::DrawConsole() const
{
	std::cout << "You're fighting a pirate, what do you want to do?" << std::endl << std::endl << "You have been killed" << std::endl;
}

void Fight::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	/*CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));*/
}
