#include "repair.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Repair::TYPE(Type::REPAIR);

void Repair::RepairCommandHandler(utils::cmd::Command& command)
{
	auto ship = &context.game.currentShip;

	int toRepair = ship->maxLifePoints - ship->lifePoints;

	if (toRepair <= 0)
	{
		context.userInterface.DrawConsole("Ship already at max hp");
	}
	else if (toRepair * 10 > context.game.Gold())
	{
		context.userInterface.DrawConsole("Insufficient amount of coins");
	}
	else {
		context.game.Repair();
		context.userInterface.DrawConsole("Fully restored your ship");
	}

	return;
}

void Repair::Initialize()
{
	// Test case
	auto ship = &context.game.currentShip; // Use the reference
	ship->lifePoints -= 2;
	// End test case

	context.userInterface.RegisterCommand("Repair", std::bind(&Repair::RepairCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand<char>("Repair", std::bind(&Repair::RepairCommandHandler, this, std::placeholders::_1));
}

void Repair::Terminate()
{
}

void Repair::DrawConsole() const
{
	std::cout << "You're at the repair centre from the port" << std::endl << std::endl;
	
	auto ship = context.game.currentShip;
	std::cout << "You're able to heal " << ship.maxLifePoints - ship.lifePoints << " lifepoints"  << std::endl;
	std::cout << "Each point will cost you 10 gold, how much do you want to spend?";
}

void Repair::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	auto ship = context.game.currentShip;

	if (ship.maxLifePoints - ship.lifePoints > 0) {
		CommandDescription repairCommandDescription;
		repairCommandDescription.command = "Repair";
		repairCommandDescription.description = "Repair your ship";
		repairCommandDescription.parameters.addItem(":amount");

		commandDescriptionsBuffer.addItem(repairCommandDescription);
	}
	
}
