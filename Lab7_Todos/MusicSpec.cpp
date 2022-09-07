#include "MusicSpec.h"

bool MusicSpec::matches(const ItemSpec& itemSpec) const {
	if (this == &itemSpec) //if comparing to self
		return true;

	// try to downcast to the required derived specification type
	auto temp{ dynamic_cast<const MusicSpec*>(&itemSpec) };
	if (nullptr == temp)
		return false; // if itemSpec doesn't refer to GameSpec (or derived) class instance

	// cast to reference type for actual comparison of properties
	const MusicSpec& otherSpec{ *temp };

	if ("" != otherSpec.get_artist()
		&& _artist != otherSpec.get_artist())
		return false;

	if ("" != otherSpec.get_album()
		&& _album != otherSpec.get_album())
		return false;

	if (0 != otherSpec.get_year()
		&& _year != otherSpec.get_year())
		return false;

	if (Genre::ANY != otherSpec.get_genre()
		&& _genre != otherSpec.get_genre())
		return false;

	return true;
}

static const char* GENRE_S[] { "ANY", "EDM", "ROCK", "JAZZ", "DUBSTEP", "TECHNO", "ELECTRO" };

void MusicSpec::send_to(ostream& os) const {
	os << _artist << ';' << _album << ';' << _year << ';' << GENRE_S[static_cast<size_t>(_genre)] << ';';
}