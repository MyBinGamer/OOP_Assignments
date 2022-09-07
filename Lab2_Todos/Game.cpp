#include "Game.h"

void Game::init(int id, const string name, const string developer, double price, const Game::Platform platform)
{
	_id = id;
	_name = name;
	_developer = developer;
	_price = price;
	_platform = platform;
}