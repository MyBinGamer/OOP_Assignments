#include "GameSpec.h"

#ifdef _MSC_VER // Visual C++ ?
#define strcasecmp _stricmp // then use the function _stricmp()
#else
#include <strings.h> // for strcasecmp() function in POSIX C++
#endif

bool GameSpec::matches(const GameSpec& otherSpec) const {
	if (this == &otherSpec) //if comparing to self
		return true;

	if (Platform::ANY != otherSpec.get_platform()
		&& _platform != otherSpec.get_platform())
		return false;

	if ("" != otherSpec.get_developer()
		&& _developer != otherSpec.get_developer())
		return false;

	return true;
}

static const char* PLATFORM_S[]{ "ANY" , "PC" , "XBOX" , "PLAYSTATION" , "NINTENDO" , "MOBILE" };

ostream& operator<<(ostream& os, GameSpec::Platform platform) {
	return os << PLATFORM_S[static_cast<size_t>(platform)];
}

ostream & operator<<(ostream & os, const GameSpec & spec) {
	spec.send_to(os);
	return os;
}

void GameSpec::send_to(ostream& os) const {
	os << _platform << ';' << _developer;
}

istream& operator>>(istream& is, GameSpec::Platform & platform) {
	if (is) {
		string tmp;
		getline(is, tmp, ';');
		if (is) {
			bool found{ false };
			for (size_t i{ 0 }; i < sizeof(PLATFORM_S) / sizeof(PLATFORM_S[0]); i++) {

				if (!strcasecmp(tmp.c_str(), PLATFORM_S[i])) {

					platform = static_cast<GameSpec::Platform>(i);
					found = true;
					break;
				}
			}

			if (!found)
				platform = GameSpec::Platform::ANY;
		}
	}
	return is;
}
istream& operator>>(istream& is, GameSpec& spec) {
	spec.recv_from(is);
	return is;
}
void GameSpec::recv_from(istream& is) {
	try {
		if (is)
			is >> _platform;
		if (is) {
			getline(is >> ws, _developer, ';');
			if (_developer.empty()) throw logic_error("Input developer ia empty");
		}
	}
	catch (logic_error & le) {
		cerr << "You got an error: " << le.what() << endl;
		terminate();
	}
}