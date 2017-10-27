#include "shop.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Shop::TYPE(Type::SHOP);

void Shop::BuyCommandHandler(utils::cmd::Command& command)
{
}

void Shop::SellCommandHandler(utils::cmd::Command& command)
{
}

void Shop::Initialize()
{
}

void Shop::Terminate()
{
}

void Shop::DrawConsole() const
{
	std::cout << "You're at the shop, what do you want to do?";
}

void Shop::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription buyCommandDescription;
	buyCommandDescription.command = "Buy";
	buyCommandDescription.description = "Buy a item from the shop";
	buyCommandDescription.parameters.addItem("itemname");

	CommandDescription sellCommandDescription;
	sellCommandDescription.command = "Sell";
	sellCommandDescription.description = "Sell a item from your ships cabin";
	sellCommandDescription.parameters.addItem("itemname");

	commandDescriptionsBuffer.addItem(buyCommandDescription);
	commandDescriptionsBuffer.addItem(sellCommandDescription);
}