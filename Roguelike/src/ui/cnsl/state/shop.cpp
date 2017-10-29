#include "shop.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Shop::TYPE(Type::SHOP);

void Shop::BuyCommandHandler(utils::cmd::Command& command)
{
	std::string itemName = command.GetParameter<std::string>(0);

	for (auto item : context.game.items)
	{
		if (itemName.compare(item->name) == 0) {
			if (context.game.BuyItem(*item))
				context.userInterface.DrawConsole("You succesfully bought the requested item");
			else
				context.userInterface.DrawConsole("Failed to buy the requested item, check your cash and load size");
			return;
		}
	}

	context.userInterface.DrawConsole("Could not find the item");
}

void Shop::SellCommandHandler(utils::cmd::Command& command)
{
	std::string itemName = command.GetParameter<std::string>(0);

	for (auto item : context.game.currentShip.items)
	{
		if (itemName.compare(item->name) == 0) {
			if (context.game.SellItem(*item))
				context.userInterface.DrawConsole("You succesfully bought the requested item");
			else
				context.userInterface.DrawConsole("Failed to buy the requested item, check your cash and load size");
			return;
		}
	}

	context.userInterface.DrawConsole("Could not find the item");
}

void Shop::Initialize()
{
	context.userInterface.RegisterCommand<std::string>("Buy", std::bind(&Shop::BuyCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand<std::string>("Sell", std::bind(&Shop::SellCommandHandler, this, std::placeholders::_1));
}

void Shop::Terminate()
{
	context.userInterface.UnregisterCommand("Buy");
	context.userInterface.UnregisterCommand("Sell");
}

void Shop::DrawConsole() const
{
	std::cout << "You're at the shop." << std::endl;
	std::cout << "You currently have " << context.game.Gold() << " gold" << std::endl << std::endl;

	if (context.game.currentShip.items.size() > 0)
	{
		std::cout << "You posses the following items" << std::endl;
		for (auto item : context.game.currentShip.items) {
			std::cout << item->name << " x " << item->amount << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "name,		price,	amount" << std::endl;
	for (auto item : context.game.currentPort.buyableItems)
	{
		int strlen = std::strlen(item->name);

		std::cout	<< item->name << ",	" << (strlen < 8 ? "	": "")
					<< item->price << ",	"
					<< item->amount << ",	" << std::endl;
	}

	std::cout << "so which item will it be?";
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
