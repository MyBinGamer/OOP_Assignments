#pragma once
#include "ItemSpec.h"
#include <string>
#include <cstring>


using namespace std;

class GameSpec : public ItemSpec {
public:
	enum class Platform { ANY, PC, XBOX, PLAYSTATION, NINTENDO, MOBILE };
	GameSpec() = default;
	GameSpec(Platform platform, const string developer)
		: _developer{ developer }, _platform{ platform } {}

	Platform get_platform() const { return _platform; }
	string get_developer() const { return _developer; }
	bool matches(const ItemSpec& otherSpec) const override;

	void send_to(ostream& os) const override;

private:
	string _developer;
	Platform _platform;
};