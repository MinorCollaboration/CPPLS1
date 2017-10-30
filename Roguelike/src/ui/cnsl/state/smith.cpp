#include "smith.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Smith::TYPE(Type::SMITH);

void Smith::BuyCommandHandler(utils::cmd::Command& command)
{
	utils::CharString cannonType = command.GetParameter<utils::CharString>(0);
	int amount = 1;
	utils::CharString amountParam = command.GetParameter<utils::CharString>(1);
	if (atoi(amountParam))
	{
		amount = atoi(amountParam);
	}
	else
	{
		context.userInterface.DrawConsole("Not a valid amount");
		delete[] amountParam.str;
		delete[] cannonType.str;
		return;
	}

	game::cannonWeight cw;
	if (std::strcmp(cannonType, "light") == 0) cw = game::cannonWeight::LIGHT;
	else if (std::strcmp(cannonType, "normal") == 0) cw = game::cannonWeight::MEDIUM;
	else if (std::strcmp(cannonType, "heavy") == 0) cw = game::cannonWeight::HEAVY;
	else {
		context.userInterface.DrawConsole("Not a valid cannon type, try lowercase");
		delete[] amountParam.str;
		delete[] cannonType.str;
		return;
	}

	if (cw == game::cannonWeight::HEAVY && context.game.currentShip.size == game::shipSize::klein) {
		context.userInterface.DrawConsole("This cannon can not be placed at your ship, its too heavy");
		delete[] amountParam.str;
		delete[] cannonType.str;
		return;
	}

	bool result = context.game.BuyCannon(cw, amount);

	if (!result)
		context.userInterface.DrawConsole("Could not buy that cannon, do you have enough space remaining?");
	else
		context.userInterface.DrawConsole("We bought one or more of the cannons of the given type");
	
	delete[] amountParam.str;
	delete[] cannonType.str;
	return;
}

void Smith::SellCommandHandler(utils::cmd::Command& command)
{
	utils::CharString cannonType = command.GetParameter<utils::CharString>(0);
	int amount = 1;
	utils::CharString amountParam = command.GetParameter<utils::CharString>(1);
	if (atoi(amountParam))
	{
		amount = atoi(amountParam);
	}
	else
	{
		context.userInterface.DrawConsole("Not a valid amount");
		delete[] amountParam.str;
		delete[] cannonType.str;
		return;
	}

	game::cannonWeight cw;
	if (std::strcmp(cannonType, "light") == 0) cw = game::cannonWeight::LIGHT;
	else if (std::strcmp(cannonType, "normal") == 0) cw = game::cannonWeight::MEDIUM;
	else if (std::strcmp(cannonType, "heavy") == 0) cw = game::cannonWeight::HEAVY;
	else {
		context.userInterface.DrawConsole("Not a valid cannon type, try lowercase");
		delete[] amountParam.str;
		delete[] cannonType.str;
		return;
	}
	
	

	bool result = context.game.SellCannon(cw, amount);

	if (!result)
		context.userInterface.DrawConsole("Could not sell a cannon of that type");
	else
		context.userInterface.DrawConsole("We sold one or more of the cannons of the given type");
	
	delete[] amountParam.str;
	delete[] cannonType.str;
	return;
}

void Smith::Initialize()
{
	context.userInterface.RegisterCommand<utils::CharString, utils::CharString>("Buy", std::bind(&Smith::BuyCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand<utils::CharString, utils::CharString>("Sell", std::bind(&Smith::SellCommandHandler, this, std::placeholders::_1));
}

void Smith::Terminate()
{
	context.userInterface.UnregisterCommand("Buy");
	context.userInterface.UnregisterCommand("Sell");
}

void Smith::DrawConsole() const
{
	std::cout << "You're at the smith, here you can buy or sell your cannons" << std::endl << std::endl;
	std::cout << "You have " << context.game.Gold() << " gold coins. What do you want to do?" << std::endl;

	if (context.game.currentShip.cannons.size() > 0) {
		std::cout << "You current loadout is: " << std::endl;
		for (auto cannon : context.game.currentShip.cannons) {
			if (cannon->amount > 0) {
				switch (cannon->weight) {
				case game::cannonWeight::LIGHT: std::cout << cannon->amount << " light cannon(s)" << std::endl; break;
				case game::cannonWeight::MEDIUM: std::cout << cannon->amount << " medium cannon(s)" << std::endl; break;
				case game::cannonWeight::HEAVY: std::cout << cannon->amount << " heavy cannon(s)" << std::endl; break;
				}
			}
			
		}
	}

	std::cout << "You have a total space for " << context.game.currentShip.cannonSize << " cannons";
}

void Smith::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription buyCommandDescription;
	buyCommandDescription.command = "Buy";
	buyCommandDescription.description = "Buy a new cannon";
	buyCommandDescription.parameters.addItem("light|normal|heavy");
	buyCommandDescription.parameters.addItem("amount");

	CommandDescription sellCommandDescription;
	sellCommandDescription.command = "Sell";
	sellCommandDescription.description = "Sell a cannon";
	sellCommandDescription.parameters.addItem("light|normal|heavy");
	sellCommandDescription.parameters.addItem("amount");

	commandDescriptionsBuffer.addItem(buyCommandDescription);
	commandDescriptionsBuffer.addItem(sellCommandDescription);
}
