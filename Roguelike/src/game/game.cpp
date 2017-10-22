#include "game.h"
#include <typeinfo>

#include <boost\algorithm\string.hpp>

using namespace game;

Game::Game() :
	isRunning(false),
	isCleared(true),
	enableRandomPirates(true),
	dungeonLayer(0)
{
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
	Clear();
}

game::Game::Game(const Game & other)
{
	isRunning = &other.isRunning;
	isCleared = &other.isCleared;
	enableRandomPirates = &other.enableRandomPirates;
	dungeon = other.dungeon;
	dungeonLayer = other.dungeonLayer;
}

void Game::Start(const int x, const int y, const int z)
{
	if (IsRunning())
		throw std::system_error(Error::GAME_ALREADY_RUNNING);

	// Put the hero in a random room.
	dungeonLayer = z;

	isRunning = true;
	isCleared = false;
}

void Game::Start()
{
	if (IsRunning())
		throw std::system_error(Error::GAME_ALREADY_RUNNING);

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
	dungeon.Clear();
	dungeonLayer = 0;

	isCleared = true;
}

void Game::SetDungeon(const Dungeon& dungeon)
{
	if (!IsCleared())
		throw std::system_error(Error::GAME_NOT_CLEARED);

	this->dungeon = dungeon;
}

const Dungeon& Game::GetDungeon() const
{
	return dungeon;
}

void Game::RandomizeDungeon(const unsigned int layerCount, const unsigned int width, const unsigned int height, const unsigned int seed)
{
	dungeon.Randomize(layerCount, width, height, seed);
	dungeonSeed = seed;
}


void Game::OnMove()
{
	OnChange(); // It's outside the if so will always be called after a movement
}

void Game::OnChange()
{
	//WriteHero(std::ofstream(HERO_FILES_FOLDER + '/' + hero.name + HERO_FILE_EXTENSION), hero);
}

int Game::GetDungeonLayer()
{
	return dungeonLayer;
}

