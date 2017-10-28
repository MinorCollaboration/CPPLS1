#include "game.h"
#include <typeinfo>

using namespace game;

Game::Game() :
	isRunning(false),
	isCleared(true),
	enableRandomPirates(true)
	//,ports(game::GetAvailablePorts())
{
	ports = game::GetAvailablePorts();
	ships = game::GetAvailableShips();
	cannons = game::GetAvailableCannons();

	//int distanceSame = game::GetPortDistance(*ports[0], *ports[0]);
	//int distanceDiff = game::GetPortDistance(*ports[0], *ports[2]);
}

/** Copy assignment operator */
Game & game::Game::operator=(const Game & other)
{
	Game tmp(other);         // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

Game::~Game() noexcept
{
	for (auto port : ports)
		delete port->name;

	for (auto ship : ships)
		delete ship->type;

	ports.clear();
	ships.clear();
	cannons.clear();
	Clear();
}

game::Game::Game(const Game & other)
{
	isRunning = &other.isRunning;
	isCleared = &other.isCleared;
	enableRandomPirates = &other.enableRandomPirates;
	ports = other.ports;
}

/*void Game::Start(const int x, const int y, const int z)
{
	if (IsRunning())
		throw std::system_error(Error::GAME_ALREADY_RUNNING);

	isRunning = true;
	isCleared = false;
}*/

void Game::Start()
{
	if (IsRunning())
		throw std::system_error(Error::GAME_ALREADY_RUNNING);

	currentPort = *ports[utils::random(ships.size() - 1)];
	currentShip = *ships[utils::random(ships.size() - 1)];

	for (int i = 0; i < utils::random(currentShip.cannonSize - 1); i++)
	{
		currentShip.AddCannon(cannons[utils::random(cannons.size() - 1)]);
	}

	AddGold(1000); // Starting cash

	isRunning = true;
	isCleared = false;
}

void Game::Stop()
{
	if (!IsRunning())
		throw std::system_error(Error::GAME_NOT_RUNNING);

	isRunning = false;
}

bool Game::IsRunning() const
{
	return isRunning;
}

bool Game::IsCleared() const
{
	return isCleared;
}

void Game::Clear()
{
	if (IsRunning())
		Stop();

	//for_each(encounterableItems.begin(), encounterableItems.end(), std::default_delete<items::Item>());

	isCleared = true;
}

void Game::UseGold(const int amount)
{
	if (goldPieces - amount > 0)
		goldPieces -= amount;
	else
		throw std::system_error(Error::NOT_ENOUGH_GOLD);
}

void Game::AddGold(const int amount)
{
	goldPieces += amount;
}

int Game::Gold() const
{
	return goldPieces;
}

void Game::Repair()
{
	int toRepair = currentShip.maxLifePoints - currentShip.lifePoints;

	if (toRepair * 10 <= Gold()) {
		UseGold(toRepair * 10);
		currentShip.lifePoints = currentShip.maxLifePoints;
	}
	else
		throw std::system_error(Error::NOT_ENOUGH_GOLD);
}

void Game::LeavePort(Port& destination)
{
	remaingSailTurns = game::GetPortDistance(currentPort, destination);
	destinationPort = &destination;
}

void Game::EnterPort()
{
	currentPort = *destinationPort;
	destinationPort = nullptr;
}

void Game::SetSail(game::Wind wind)
{
	int stormOutput = utils::random(100); // StormOutputChance

	switch (wind) {
	
	case game::Wind::breeze :
		if (currentShip.weight == game::shipWeight::licht) {
			remaingSailTurns -= 1;
		} // else: no wind, do nothing
		break;
	case game::Wind::weak :
		if (currentShip.weight != game::shipWeight::log) {
			remaingSailTurns -= 1;
		}
		break;
	case game::Wind::normal :
		remaingSailTurns -= 1;
		break;
	case game::Wind::strong :
		remaingSailTurns -= 1;
		remaingSailTurns -= 1;
		break;
	case game::Wind::storm :
		currentShip.lifePoints -= utils::random(currentShip.lifePoints);

		if (stormOutput < 40)
			remaingSailTurns += 1; // you got offcourse, you need a extra turn
		else if (stormOutput < 80) // take a remaining of 40 procent
			break;
		else // take the remaining 20 procent
			remaingSailTurns -= 1; // you got blown at the right direction, one turn less;
		
		break;
	case game::Wind::none :
	default:
		break; // No wind, so no movement
	}

	if (remaingSailTurns > 0)
	{
		if (utils::random(100) <= PIRATE_SPAWN_CHANCE) // Output is smaller than (or equal to) PIRATE_SPANW_CHANCE
		{
			pirateShip = ships[utils::random(ships.size() - 1)];
		}
	}
	else // else: the port defences destroyed the pirate, we can safely enter the port
	{
		EnterPort();
	}
}

void Game::ShootPlayer()
{
	for (auto cannon : pirateShip->cannons)
	{
		currentShip.lifePoints -= cannon->Shoot();
		if (currentShip.lifePoints <= 0)
			break;
	}
}

void Game::ShootPirate()
{
	for (auto cannon : currentShip.cannons)
	{
		pirateShip->lifePoints -= cannon->Shoot();
		if (pirateShip->lifePoints <= 0) {
			pirateShip = nullptr;
			break;
		}
	}
}

void Game::Surrender()
{
	pirateShip = nullptr;
}

void Game::OnMove()
{
	OnChange(); // It's outside the if so will always be called after a movement
}

void Game::OnChange()
{
	//WriteHero(std::ofstream(HERO_FILES_FOLDER + '/' + hero.name + HERO_FILE_EXTENSION), hero);
}