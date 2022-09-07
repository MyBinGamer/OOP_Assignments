#pragma once
#ifndef GAMESPEC
#define GAMESPEC
#include <string>
#include <cstddef> // for std::size_t

using namespace std;

class GameSpec {
public:
	enum class Platform { ANY, PC, XBOX, PLAYSTATION, NINTENDO, MOBILE };

	GameSpec() = default;
	GameSpec(Platform platform, string developer)
		: _platform{ platform }, _developer{ developer } {}

	Platform get_platform() const { return _platform; }
	string get_developer() const { return _developer; }

private:
	string _developer;
	Platform _platform;
};
#endif