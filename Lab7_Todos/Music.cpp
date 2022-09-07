#include "Music.h"

void Music::send_to(ostream& os) const {
	Item::send_to(os);
	os << _name << ';'
		<< _length;
	if (_spec) {
		os << ';';
		_spec->send_to(os);
	}
}
