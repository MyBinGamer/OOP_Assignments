#pragma once
#include <string>
#include <cstddef> // for std::size_t
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

class GameSpec {
public:
	enum class Platform { ANY, PC, XBOX, PLAYSTATION, NINTENDO, MOBILE };
	GameSpec() = default;
	GameSpec(const string developer, Platform platform)
		: _developer{ developer }, _platform{ platform } {}

	Platform get_platform() const { return _platform; }
	string get_developer() const { return _developer; }
	bool matches(const GameSpec& otherSpec) const;

	void send_to(ostream& os) const;
	void recv_from(istream& is);
	friend istream& operator>>(istream& is, GameSpec& spec);

private:
	string _developer;
	Platform _platform;
};

istream& operator>>(istream& is, GameSpec::Platform& platform);
ostream& operator<<(ostream& os, GameSpec::Platform platform);
ostream& operator<<(ostream& os, const GameSpec& spec);
