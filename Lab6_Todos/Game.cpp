#include "Game.h"

ostream& operator<<(ostream& os, const Game& item) {
	item.send_to(os);
	return os;
}

void Game::send_to(ostream& os) const {
	os<< _id << ';'
		<< _name << ';'
		<< _price;
	if (_spec) {
		os << ';';
		_spec->send_to(os);
	}
}

istream& operator>>(istream& is, Game& item) {
	item.recv_from(is);
	return is;
}

void Game::recv_from(istream& is) {
	try {
		if (is) {
			(is >> _id).ignore();
			if (_id <=0) throw logic_error("Invalid id value");
		}

		if (is) {
			getline(is >> ws, _name, ';');
			if (_name.empty()) throw logic_error("Input name is empty");
		}

		if (is) {
			(is >> _price).ignore();
			if (_price <=0.0) throw logic_error("Input price is invalid");
		}

	}
	catch (logic_error& le) {
		cerr << "You have got an error: " << le.what() << endl;
		terminate();
	}
	auto temp_spec{ make_shared<GameSpec>() };
	temp_spec->recv_from(is);
	_spec = temp_spec;

}