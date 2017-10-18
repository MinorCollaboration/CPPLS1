#ifndef UI_CNSL_USERINTERFACE_HEADER_INCLUDED
#define UI_CNSL_USERINTERFACE_HEADER_INCLUDED

#include <iostream>
#include <functional>

#ifdef _WIN32
  #include <stdlib.h>
#endif // _WIN32

#include <utils/cmd/commandhandler.hpp>
#include <utils/cmd/command.hpp>

#include "../../game/game.h"

#include "../userinterfacebase.h"

#include "commanddescription.h"

#include "state/factory.h"
#include "state/base.h"
#include "state/type.h"
#include "state/context.h"

namespace ui
{
	namespace cnsl
	{
		class UserInterface :
			public UserInterfaceBase
		{
			typedef state::BaseInterface** StatesContainerNew;
			typedef std::vector<state::BaseInterface*> StatesContainer;
		private:
			std::ifstream&		inputStream;

			StatesContainer		states;
			state::Context		stateContext;

			bool				shouldExit		= false;
			bool				gameOver		= false;

			void ExitCommandHandler(utils::cmd::Command& command);
			void BackCommandHandler(utils::cmd::Command& command);
		public:
			UserInterface(game::Game& game) noexcept;
			UserInterface(game::Game& game, std::ifstream& inputStream) noexcept;

			~UserInterface() noexcept;

			void Start() override;

			state::BaseInterface* GetState() const noexcept;
			void SetState(const state::Type type);
			void GoToPreviousState();

			void ClearConsole() const noexcept;
			void DrawConsole() const;
			void DrawConsole(const char* extraMessage) const;
			void GameOver();
			void Exit() noexcept;
			std::vector<CommandDescription> GetAvailableCommands() const;
		};
	}
}

#endif // UI_CNSL_USERINTERFACE_HEADER_INCLUDED