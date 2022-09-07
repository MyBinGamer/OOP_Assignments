#include "GameSpec.h"

bool GameSpec::matches(const ItemSpec & itemSpec) const {
	if (this == &itemSpec) //if comparing to self
		return true;

	// try to downcast to the required derived specification type
	auto temp{ dynamic_cast<const GameSpec*>(&itemSpec) };
	if (nullptr == temp)
		return false; // if itemSpec doesn't refer to GameSpec (or derived) class instance

	// cast to reference type for actual comparison of properties
	const GameSpec& otherSpec{ *temp };

	if (Platform::ANY != otherSpec.get_platform()
		&& _platform != otherSpec.get_platform())
		return false;

	if ("" != otherSpec.get_developer()
		&& _developer != otherSpec.get_developer())
		return false;

	return true;
}

static const char* PLATFORM_S[]{ "ANY" , "PC" , "XBOX" , "PLAYSTATION" , "NINTENDO" , "MOBILE" };

void GameSpec::send_to(ostream& os) const {
	os << PLATFORM_S[static_cast<size_t>(_platform)] << ';' << _developer <<';';
}