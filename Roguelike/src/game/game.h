#ifndef GAME_GAME_HEADER_INCLUDED
#define GAME_GAME_HEADER_INCLUDED

#include <system_error>
#include <vector>

#include "errorcategory.h"
#include "dungeon.h"

#include "nodes/room.h"

namespace game
{
	class Game
	{
	private:
		bool			isRunning;
		bool			isCleared;
		bool			enableRandomPirates;
		const double	PIRATE_SPAWN_CHANCE = 35;
		unsigned int	dungeonSeed;

		Dungeon			dungeon;

		unsigned int	dungeonLayer;

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

		int GetDungeonLayer();

		void SetDungeon(const Dungeon& dungeon);
		const Dungeon& GetDungeon() const;

		void RandomizeDungeon(const unsigned int layerCount, const unsigned int width, const unsigned int height, const unsigned int seed);

		void OnChange();
	}; // class Game


} // namespace game

#endif // #ifndef GAME_GAME_HEADER_INCLUDED
