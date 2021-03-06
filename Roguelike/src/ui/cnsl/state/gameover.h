#ifndef UI_CNSL_STATE_GAMEOVER_HEADER_INCLUDED
#define UI_CNSL_STATE_GAMEOVER_HEADER_INCLUDED

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
			class Gameover :
				public Base<Gameover>
			{
			private:
				void SaveCommandHandler(utils::cmd::Command& command);
			public:
				static const Type TYPE;

				using Base::Base;

				void Initialize() override;
				void Terminate() override;

				void DrawConsole() const override;
				void GetAvailableCommands(utils::Array<CommandDescription>& commandDescriptionsBuffer) const override;
			};
		} // namespace ui
	} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_GAMEOVER_HEADER_INCLUDED
