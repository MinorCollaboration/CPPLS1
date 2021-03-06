#ifndef UI_CNSL_STATE_SAIL_HEADER_INCLUDED
#define UI_CNSL_STATE_SAIL_HEADER_INCLUDED

#include <iostream>

#include "../commanddescription.h"
#include "../userinterface.h"

#include "base.h"
#include "type.h"

namespace ui
{
	namespace cnsl
	{
		namespace state
		{
			class Sail : public Base<Sail>
			{
			private:
				game::Wind GetRandomWind();
				void NextCommandHandler(utils::cmd::Command& command);
				game::Wind wind;
			public:
				static const Type TYPE;

				using Base::Base;

				void Initialize() override;
				void Terminate() override;

				void DrawConsole() const override;
				void GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const override;
			};
		}
	}
}

#endif