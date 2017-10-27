#include "port.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Port::TYPE(Type::PORT);

void Port::Initialize()
{
	context.userInterface.RegisterCommand<>("Shop", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::SHOP); });
	context.userInterface.RegisterCommand<>("Smith", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::SMITH); });
	context.userInterface.RegisterCommand<>("Harbor", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::HARBOR); });
	context.userInterface.RegisterCommand<>("Sail", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::SAIL); });
	context.userInterface.RegisterCommand<>("Repair", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::REPAIR); });
}

void Port::Terminate()
{
	context.userInterface.UnregisterCommand("Shop");
	context.userInterface.UnregisterCommand("Smith");
	context.userInterface.UnregisterCommand("Harbor");
	context.userInterface.UnregisterCommand("Sail");
	context.userInterface.UnregisterCommand("Repair");
}

void Port::DrawConsole() const
{
	std::cout << "You're at the port of " << context.game.currentPort.name << ", what do you want to do?";
}

void Port::GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription shopCommandDescription;
	shopCommandDescription.command = "Shop";
	shopCommandDescription.description = "Go to the shop to by items";

	CommandDescription smithCommandDescription;
	smithCommandDescription.command = "Smith";
	smithCommandDescription.description = "Get to the smith to buy or sell cannons";

	CommandDescription harborCommandDescription;
	harborCommandDescription.command = "Harbor";
	harborCommandDescription.description = "Visit the harbor for to exchange your ship for a new ship";

	CommandDescription sailCommandDescription;
	sailCommandDescription.command = "Sail";
	sailCommandDescription.description = "Set sail to the next port";
	sailCommandDescription.parameters.addItem("port name");

	CommandDescription repairCommandDescription;
	repairCommandDescription.command = "Repair";
	repairCommandDescription.description = "Get a damage report and decide how much you want to repair";

	commandDescriptionsBuffer.addItem(shopCommandDescription);
	commandDescriptionsBuffer.addItem(smithCommandDescription);
	commandDescriptionsBuffer.addItem(harborCommandDescription);
	commandDescriptionsBuffer.addItem(sailCommandDescription);
	commandDescriptionsBuffer.addItem(repairCommandDescription);
}
