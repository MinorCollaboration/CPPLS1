#include "fight.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Fight::TYPE(Type::FIGHT);

void Fight::ShootCommandHandler(utils::cmd::Command& command)
{
	context.game.ShootPirate();

	if (context.game.pirateShip != nullptr) {
		context.game.ShootPlayer();
		if (context.game.currentShip.lifePoints <= 0) {
			context.userInterface.SetState(Type::GAMEOVER);
		}
		context.userInterface.DrawConsole("You ended up in a fight, no one won so far");
		return;
	}
	context.userInterface.SetState(Type::SAIL);
}

void Fight::SurrenderCommandHandler(utils::cmd::Command& command)
{
	context.game.Surrender();

	context.userInterface.SetState(Type::SAIL);
	context.userInterface.DrawConsole("The pirates took all the goods they could carry and throu the rest overboard");
	return;
}

void Fight::FleeCommandHandler(utils::cmd::Command& command)
{
	int escapeChance = 0;
	switch (context.game.currentShip.weight) {
	case game::shipWeight::licht:	escapeChance += 5; break;
	case game::shipWeight::normaal: escapeChance += 30; break;
	case game::shipWeight::log:		escapeChance += 50; break;
	}

	switch (context.game.pirateShip->weight) {
	case game::shipWeight::normaal: escapeChance += 10; break;
	case game::shipWeight::log:		escapeChance += 25; break;
	}

	context.game.ShootPlayer();
	if (context.game.currentShip.lifePoints <= 0) {
		context.userInterface.SetState(Type::GAMEOVER);
		return;
	}

	if (utils::random(0, 100) < escapeChance) {
		context.game.pirateShip = nullptr;
		context.userInterface.SetState(Type::SAIL);
		return;
	}
	context.userInterface.DrawConsole("You failed to escape");
}

void Fight::Initialize()
{
	context.userInterface.RegisterCommand("Shoot", std::bind(&Fight::ShootCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand("Surrender", std::bind(&Fight::ShootCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand("Flee", std::bind(&Fight::ShootCommandHandler, this, std::placeholders::_1));
}

void Fight::Terminate()
{
	context.userInterface.UnregisterCommand("Shoot");
	context.userInterface.UnregisterCommand("Surrender");
	context.userInterface.UnregisterCommand("Flee");
}

void Fight::DrawConsole() const
{
	std::cout << "You're fighting a pirate, what do you want to do?";
	std::cout << "you have " << context.game.currentShip.lifePoints << " lifepoints remaining" << std::endl << std::endl;
}

void Fight::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription shootCommandDescription;
	shootCommandDescription.command = "Shoot";
	shootCommandDescription.description = "Try to kill the pirates before they kill you";

	CommandDescription surrenderCommandDescription;
	surrenderCommandDescription.command = "Surrender";
	surrenderCommandDescription.description = "Let them take your goods and move on";

	CommandDescription fleeCommandDescription;
	fleeCommandDescription.command = "Flee";
	fleeCommandDescription.description = "Try to escape them";

	commandDescriptionsBuffer.addItem(shootCommandDescription);
	commandDescriptionsBuffer.addItem(surrenderCommandDescription);
	commandDescriptionsBuffer.addItem(fleeCommandDescription);
}
