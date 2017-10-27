#include "repair.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Repair::TYPE(Type::REPAIR);

void Repair::RepairCommandHandler(utils::cmd::Command& command)
{
	context.userInterface.Exit();
}

void Repair::Initialize()
{
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
	/*CommandDescription saveCommandDescription;
	saveCommandDescription.command = "Save";
	saveCommandDescription.description = "Save the hero stats and exit the game";

	commandDescriptionsBuffer.emplace_back(std::move(saveCommandDescription));*/
}
