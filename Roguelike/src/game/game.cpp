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

void Game::OnMove()
{
	OnChange(); // It's outside the if so will always be called after a movement
}

void Game::OnChange()
{
	//WriteHero(std::ofstream(HERO_FILES_FOLDER + '/' + hero.name + HERO_FILE_EXTENSION), hero);
}