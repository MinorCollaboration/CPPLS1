#ifndef UI_CNSL_USERINTERFACE_HEADER_INCLUDED
#define UI_CNSL_USERINTERFACE_HEADER_INCLUDED

#include <iostream>
#include <utils/array.hpp>
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
		public utils::cmd::CommandHandler,
		public UserInterfaceBase
	{
		typedef utils::Array<state::BaseInterface*> StatesContainer;

	private:
		std::istream&		inputStream;

		StatesContainer		states;
		state::Context		stateContext;

		bool				shouldExit		= false;
		bool				gameOver		= false;

		void ExitCommandHandler(utils::cmd::Command& command);
		void BackCommandHandler(utils::cmd::Command& command);

	public:
		UserInterface(game::Game& game) noexcept;
		UserInterface(game::Game& game, std::istream& inputStream) noexcept;

		~UserInterface() noexcept;

		void Start() override;

		state::BaseInterface* GetState() const noexcept;
		void SetState(const state::Type type);
		void GoToPreviousState();

		void ClearConsole() const noexcept;
		void DrawConsole() const;
		void DrawConsole(const std::string extraMessage) const;
		void GameOver();
		void NewGame();
		void Exit() noexcept;
		utils::Array<CommandDescription> GetAvailableCommands() const;
	}; // class UserInterface
} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_USERINTERFACE_HEADER_INCLUDED
