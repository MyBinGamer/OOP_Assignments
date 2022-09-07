#pragma once
#ifndef GAME
#define GAME
#include <string>

using namespace std;

class Game
{
public:
	enum class Platform {ANY, PC, XBOX, PLAYSTATION, NINTENDO, MOBILE};
	void init(int id, const string name, const string developer, double price, const Game::Platform platform);
	int get_id() const { return _id; }
	string get_name() const { return _name; }
	string get_developer() const { return _developer; }
	double get_price() const { return _price; }
	Game::Platform get_platform() const { return _platform;  }

private:
	int _id;
	string _name;
	string _developer;
	double _price;
	Game::Platform _platform;
};

#endif