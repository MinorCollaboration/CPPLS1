#include "smith.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Smith::TYPE(Type::SMITH);

void Smith::BuyCommandHandler(utils::cmd::Command& command)
{
}

void Smith::SellCommandHandler(utils::cmd::Command& command)
{
}

void Smith::Initialize()
{
}

void Smith::Terminate()
{
}

void Smith::DrawConsole() const
{
	std::cout << "You're at the smith, here you can buy or sell your cannons" << std::endl << std::endl;
	std::cout << "What do you want to do?";
}

void Smith::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription buyCommandDescription;
	buyCommandDescription.command = "Buy";
	buyCommandDescription.description = "Buy a new cannon";
	buyCommandDescription.parameters.addItem("light|middle|heavy");
	buyCommandDescription.parameters.addItem(":amount");

	CommandDescription sellCommandDescription;
	sellCommandDescription.command = "Sell";
	sellCommandDescription.description = "Sell a cannon";
	sellCommandDescription.parameters.addItem("light|middle|heavy");
	sellCommandDescription.parameters.addItem(":amount");

	commandDescriptionsBuffer.addItem(buyCommandDescription);
	commandDescriptionsBuffer.addItem(sellCommandDescription);
}
