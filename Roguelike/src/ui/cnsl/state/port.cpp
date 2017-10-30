#include "port.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Port::TYPE(Type::PORT);

void Port::SailCommandHandler(utils::cmd::Command& command)
{
	utils::CharString destinationName = command.GetParameter<utils::CharString>(0);

	for (auto port : context.game.ports) {
		char* portName = &utils::chartolower(port->name);
		if (std::strcmp(destinationName, portName) == 0)
		{
			if (game::GetPortDistance(*port, context.game.currentPort) == 0) {
				context.userInterface.DrawConsole("This port cannot be sailed to as it is the same or cannot be found");
			}
			else {
				context.game.LeavePort(*port);
				context.userInterface.SetState(Type::SAIL);
			}
			delete[] destinationName.str;
			delete[] portName;
			return;
		}

		delete[] portName;
	}

	context.userInterface.DrawConsole("Port does not exist");
	delete[] destinationName.str;
	return;
}

void Port::Initialize()
{
	context.userInterface.RegisterCommand("Shop", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::SHOP); });
	context.userInterface.RegisterCommand("Smith", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::SMITH); });
	context.userInterface.RegisterCommand("Harbor", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::HARBOR); });
	context.userInterface.RegisterCommand<utils::CharString>("Sail", std::bind(&Port::SailCommandHandler, this, std::placeholders::_1));
	context.userInterface.RegisterCommand("Repair", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::REPAIR); });
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
