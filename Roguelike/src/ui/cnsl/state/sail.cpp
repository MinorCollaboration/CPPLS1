#include "sail.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Sail::TYPE(Type::SAIL);

game::Wind Sail::GetRandomWind()
{
	int wind = utils::random(1, 20);

	if (wind <= 2) // we could use ints but this is more readable
		return game::Wind(game::Wind::none);
	else if (wind <= 4)
		return game::Wind(game::Wind::breeze);
	else if (wind <= 7)
		return game::Wind(game::Wind::weak);
	else if (wind <= 17)
		return game::Wind(game::Wind::normal);
	else if (wind <= 19)
		return game::Wind(game::Wind::strong);
	else if (wind <= 20)
		return game::Wind(game::Wind::storm);
	else
		return game::Wind(game::Wind::none);
}

void Sail::NextCommandHandler(utils::cmd::Command& command)
{
	wind = GetRandomWind();
	context.game.SetSail(wind);

	if (context.game.destinationPort == nullptr) {
		context.userInterface.SetState(Type::PORT);
		context.userInterface.DrawConsole("You arrived at the port");
		return;
	}
	else if (context.game.pirateShip != nullptr) {
		context.userInterface.SetState(Type::FIGHT);
		return;
	}

	context.userInterface.DrawConsole("You took your next turn");
	return;
}

void Sail::Initialize()
{
	if (context.game.destinationPort == nullptr) {
		context.userInterface.SetState(Type::PORT);
	}

	wind = GetRandomWind();
	context.game.SetSail(wind);

	if (context.game.destinationPort == nullptr) {
		context.userInterface.SetState(Type::PORT);
		context.userInterface.DrawConsole("You arrived at the port");
		return;
	}
	else if (context.game.pirateShip != nullptr) {
		context.userInterface.SetState(Type::FIGHT);
		return;
	}

	context.userInterface.RegisterCommand("Next", std::bind(&Sail::NextCommandHandler, this, std::placeholders::_1));
}

void Sail::Terminate()
{
	context.userInterface.UnregisterCommand("Next");
}

void Sail::DrawConsole() const
{
	std::cout << "You're at the middle of the sea, on your way to " << context.game.destinationPort->name << std::endl;
	std::cout << "You're " << context.game.remaingSailTurns << " miles away from it" << std::endl << std::endl;

	std::cout << "You're carrying " << context.game.currentShip.items.size() << " items" << std::endl;
	std::cout << "And you can spend " << context.game.Gold() << " when you arrive at the next port" << std::endl << std::endl;

	std::cout << "The wind is ";
	switch (wind) {
		case game::Wind::breeze: std::cout << "a small breeze"; break;
		case game::Wind::weak: std::cout << "not that great"; break;
		case game::Wind::normal: std::cout << "just enough"; break;
		case game::Wind::strong: std::cout << "strong"; break;
		case game::Wind::storm: std::cout << "way too heavy"; break;
		case game::Wind::none: default : std::cout << "laying still"; break;
	}
	std::cout << std::endl << "What do you want to do?";
}

void Sail::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription nextCommandDescription;
	nextCommandDescription.command = "Next";
	nextCommandDescription.description = "Take the next mile in your journey";

	commandDescriptionsBuffer.addItem(nextCommandDescription);
}
