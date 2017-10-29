#ifndef GAME_GAME_HEADER_INCLUDED
#define GAME_GAME_HEADER_INCLUDED

#include <system_error>

#include <utils/array.hpp>
#include <utils/int.hpp>

#include "errorcategory.h"
#include "port.h" // also includes ship.h which also includes cannon.h
#include "item.h"
#include "wind.h"

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
		CannonContainer cannons;
		ItemsContainer	items;

		Port			currentPort;
		Ship			currentShip;

		Ship*			pirateShip;
		Port*			destinationPort;
		int				remaingSailTurns;

		bool IsRunning() const;
		bool IsCleared() const;

		void UseGold(const int amount);
		void AddGold(const int amount);
		int Gold() const;

		void Repair();

		void LeavePort(Port& destination);
		void EnterPort();
		void SetSail(game::Wind);

		void ShootPirate();
		void ShootPlayer();

		void Surrender();

		bool BuyCannon(cannonWeight);
		bool BuyCannon(cannonWeight, int amount);
		bool SellCannon(cannonWeight);
		bool SellCannon(cannonWeight, int amount);

		void Clear();

		void OnChange();
	}; // class Game


} // namespace game

#endif // #ifndef GAME_GAME_HEADER_INCLUDED
