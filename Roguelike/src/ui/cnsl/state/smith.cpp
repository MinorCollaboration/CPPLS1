#include "smith.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Smith::TYPE(Type::SMITH);

void Smith::BuyCommandHandler(utils::cmd::Command& command)
{
	std::string cannonType = command.GetParameter<std::string>(0);
	int amount = 1;
	if (command.GetAmountOfParameters() > 1) {
		if (utils::isnumeric(*&command.GetParameter<std::string>(1))) {
			amount = stoi(command.GetParameter<std::string>(1));
		}
	}

	game::cannonWeight cw;
	if (cannonType.compare("light") == 0) cw = game::cannonWeight::LIGHT;
	else if (cannonType.compare("normal") == 0) cw = game::cannonWeight::MEDIUM;
	else if (cannonType.compare("heavy") == 0) cw = game::cannonWeight::HEAVY;
	else {
		context.userInterface.DrawConsole("Not a valid cannon type, try lowercase");
		return;
	}

	if (cw == game::cannonWeight::HEAVY && context.game.currentShip.size == game::shipSize::klein) {
		context.userInterface.DrawConsole("This cannon can not be placed at your ship, its too heavy");
		return;
	}

	bool result = context.game.BuyCannon(cw, amount);

	if (!result)
		context.userInterface.DrawConsole("Could not buy that cannon, do you have enough space remaining?");
	else
		context.userInterface.DrawConsole("We bought one or more of the cannons of the given type");
	return;
}

void Smith::SellCommandHandler(utils::cmd::Command& command)
{
	std::string cannonType = command.GetParameter<std::string>(0);
	int amount = 1;
	if (command.GetAmountOfParameters() > 1) {
		if (utils::isnumeric(*&command.GetParameter<std::string>(1))) {
			amount = stoi(command.GetParameter<std::string>(1));
		}
	}

	game::cannonWeight cw;
	if (cannonType.compare("light") == 0) cw = game::cannonWeight::LIGHT;
	else if (cannonType.compare("normal") == 0) cw = game::cannonWeight::MEDIUM;
	else if (cannonType.compare("heavy") == 0) cw = game::cannonWeight::HEAVY;
	else {
		context.userInterface.DrawConsole("Not a valid cannon type, try lowercase");
		return;
	}

	bool result = context.game.SellCannon(cw, amount);

	if (!result)
		context.userInterface.DrawConsole("Could not sell a cannon of that type");
	else
		context.userInterface.DrawConsole("We sold one or more of the cannons of the given type");
	return;
}

void Smith::Initialize()
{
	context.userInterface.RegisterCommand<std::string, std::string>("Buy", std::bind(&Smith::BuyCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand<std::string, std::string>("Sell", std::bind(&Smith::SellCommandHandler, this, std::placeholders::_1));
}

void Smith::Terminate()
{
	context.userInterface.UnregisterCommand("Buy");
	context.userInterface.UnregisterCommand("Sell");
}

void Smith::DrawConsole() const
{
	std::cout << "You're at the smith, here you can buy or sell your cannons" << std::endl << std::endl;
	std::cout << "You have " << context.game.Gold() << " gold coins. What do you want to do?";

	int lightCannon = 0, normalCannon = 0, heavyCannon = 0;
	for (auto cannon : context.game.currentShip.cannons) {
		switch (cannon->weight) {
		case game::cannonWeight::LIGHT: lightCannon++; break;
		case game::cannonWeight::MEDIUM: normalCannon++; break;
		case game::cannonWeight::HEAVY: heavyCannon++; break;
		}
	}

	if (lightCannon > 0 || normalCannon > 0 || heavyCannon > 0) {
		std::cout << "You current loadout is: " << std::endl;
		if (lightCannon > 0) std::cout << lightCannon << " light cannons" << std::endl;
		if (normalCannon > 0) std::cout << normalCannon << " medium cannons" << std::endl;
		if (heavyCannon > 0) std::cout << heavyCannon << " heavy cannons" << std::endl;
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
