#include "Game.h"

void Game::send_to(ostream& os) const {
	Item::send_to(os);
	os<< _name << ';'
		<< _price;
	if (_spec) {
		os << ';';
		_spec->send_to(os);
	}
}