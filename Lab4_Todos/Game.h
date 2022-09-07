#pragma once
#ifndef GAME
#define GAME
#include "GameSpec.h"
#include <string>

using namespace std;

class Game
{
public:
	enum class Platform { ANY, PC, XBOX, PLAYSTATION, NINTENDO, MOBILE };
	Game() = default;
	Game(int id, const string& name, double price, const GameSpec & spec)
		: _id{ id }, _name{ name }, _price{ price }, _spec{spec} {}
	int get_id() const { return _id; }
	string get_name() const { return _name; }
	double get_price() const { return _price; }
	GameSpec get_spec() const { return _spec; }

private:
	int _id;
	string _name;
	double _price;
	GameSpec _spec;
};

#endif