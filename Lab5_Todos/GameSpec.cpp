#include "GameSpec.h"


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
//As you see, there is nothing else to write here