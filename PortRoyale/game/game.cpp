#include "game.h"
#include <typeinfo>

using namespace game;

Game::Game() :
	isRunning(false),
	isCleared(true)
{
}

game::Game::Game(const Game & other)
{
	isRunning = &other.isRunning;
	isCleared = &other.isCleared;
}

Game & game::Game::operator=(const Game & other)
{
	Game tmp(other);
	*this = *&tmp;
	return *this;
}

Game::~Game() noexcept
{
	Clear();
}

void Game::Start(const int x, const int y)
{
	if (!IsRunning())
		throw - 2;

	isRunning = true;
	isCleared = false;
}

void Game::Start()
{
	if (!IsRunning())
		throw -2;

	isRunning = true;
	isCleared = false;
}

void Game::Stop()
{
	if (!IsRunning())
		throw -1;

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

	isCleared = true;
}