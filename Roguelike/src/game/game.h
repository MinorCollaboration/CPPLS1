#ifndef GAME_GAME_HEADER_INCLUDED
#define GAME_GAME_HEADER_INCLUDED

#include <system_error>

#include "errorcategory.h"

namespace game
{
	class Game
	{
	private:
		bool			isRunning;
		bool			isCleared;
		bool			enableRandomPirates;
		const double	PIRATE_SPAWN_CHANCE = 35;

		void OnMove();
	public:
		Game();
		~Game() noexcept;
		Game(const Game& other);
		Game &operator =(const Game& other);

		void Start(const int x, const int y, const int z);
		void Start();
		void Stop();

		bool IsRunning() const;
		bool IsCleared() const;

		void Clear();

		void OnChange();
	}; // class Game


} // namespace game

#endif // #ifndef GAME_GAME_HEADER_INCLUDED
