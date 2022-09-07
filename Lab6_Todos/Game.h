#pragma once
#include "GameSpec.h"
#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Game
{
public:
	void send_to(ostream& os) const;
	Game() = default;
	Game(int id, const string name, double price, shared_ptr<const GameSpec> spec)
		: _id{ id }, _name{ name }, _price{ price }, _spec{ spec } {}
	int get_id() const { return _id; }
	string get_name() const { return _name; }
	double get_price() const { return _price; }
	shared_ptr<const GameSpec> get_spec() const { return _spec; }

	void recv_from(istream& is);
	friend istream& operator>>(istream& is, Game& item);
private:
	int _id;
	string _name;
	double _price;
	shared_ptr<const GameSpec> _spec;
};

ostream& operator<<(ostream& os, const Game& item);