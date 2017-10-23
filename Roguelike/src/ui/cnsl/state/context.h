#ifndef UI_CNSL_STATE_CONTEXT_HEADER_INCLUDED
#define UI_CNSL_STATE_CONTEXT_HEADER_INCLUDED

#include "../../../game/game.h"

namespace ui
{
namespace cnsl
{
	class UserInterface;

namespace state
{
	class Context
	{
	public:
		Context(UserInterface& userInterface, game::Game& game) noexcept;

		UserInterface&	userInterface;
		
		game::Game&		game;
	}; // class Context
} // namespace state
} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_STATE_CONTEXT_HEADER_INCLUDED