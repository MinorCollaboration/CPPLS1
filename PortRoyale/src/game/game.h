#ifndef GAME_GAME_HEADER_INCLUDED
#define GAME_GAME_HEADER_INCLUDED

#include <system_error>
#include <vector>

#include "errorcategory.h"

namespace game
{
	class Game
	{
	private:
		bool			isRunning;
		bool			isCleared;
	public:
		Game();
		~Game() noexcept;
		Game(const Game& other);
		Game &operator =(const Game& other);

		void Start(const int x, const int y);
		void Start();
		void Stop();

		bool IsRunning() const;
		bool IsCleared() const;

		void Clear();
	};
}

#endif GAME_GAME_HEADER_INCLUDED