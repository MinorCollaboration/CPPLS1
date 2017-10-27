#include "harbor.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Harbor::TYPE(Type::HARBOR);

void Harbor::BuyCommandHandler(utils::cmd::Command& command)
{
	context.userInterface.Exit();
}

void Harbor::SellCommandHandler(utils::cmd::Command& command)
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
	std::cout << "You're fighting a pirate, what do you want to do?" << std::endl << std::endl << "You have been killed" << std::endl;
}

void Harbor::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	/*CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));*/
}
