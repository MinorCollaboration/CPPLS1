#ifndef UI_CNSL_STATE_FIGHT_HEADER_INCLUDED
#define UI_CNSL_STATE_FIGHT_HEADER_INCLUDED

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
			class Fight : public Base<Fight>
			{
			private:
				void ShootCommandHandler(utils::cmd::Command& command);
				void SurrenderCommandHandler(utils::cmd::Command& command);
				void FleeCommandHandler(utils::cmd::Command& command);
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