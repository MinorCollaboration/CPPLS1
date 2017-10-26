#ifndef GAME_GAME_HEADER_INCLUDED
#define GAME_GAME_HEADER_INCLUDED

#include <system_error>

#include <utils/array.hpp>
#include <utils/int.hpp>

#include "errorcategory.h"
#include "port.h"

namespace game
{
	class Game
	{
	private:
		int				goldPieces;
		bool			isRunning;
		bool			isCleared;
		bool			enableRandomPirates;
		const double	PIRATE_SPAWN_CHANCE = 35;
		
		//PortsContainer	ports; // Currently 24 ports available

		void OnMove();
	public:
		Game();
		~Game() noexcept;
		Game(const Game& other);
		Game &operator =(const Game& other);

		//void Start(const int x, const int y, const int z);
		void Start();
		void Stop();

		PortsContainer	ports;
		ShipsContainer	ships;

		Port			currentPort;
		Ship			currentShip;

		bool IsRunning() const;
		bool IsCleared() const;

		void UseGold(const int amount);
		void AddGold(const int amount);
		int Gold() const;

		void Clear();

		void OnChange();
	}; // class Game


} // namespace game

#endif // #ifndef GAME_GAME_HEADER_INCLUDED
