#pragma once
#ifndef GAME
#define GAME

#include "GameSpec.h"
#include "Item.h"
#include <string>
#include <memory>

using namespace std;

class Game : public Item
{
public:
	void send_to(ostream& os) const override;
	Game() = default;
	Game(int id, const string name, double price, shared_ptr<const GameSpec> spec)
		: Item(id, spec), _name{ name }, _price{ price } {}
	string get_name() const { return _name; }
	double get_price() const { return _price; }
	shared_ptr<const GameSpec> get_spec() const { return _spec; }

private:
	string _name;
	double _price;
	shared_ptr<const GameSpec> _spec;
};
#endif