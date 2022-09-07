#pragma once
#ifndef MUSIC
#define MUSIC
#include "Item.h"
#include "MusicSpec.h"
#include <string>
#include <memory>

using namespace std;

class Music : public Item
{
public:
	Music() = default;
	Music(int id, shared_ptr<const MusicSpec> spec, const string name,
		double length)
		: Item(id, spec), _name{name}, _length{ length } {}

	string get_name() const { return _name; }
	double get_length() const { return _length; }
	shared_ptr<const MusicSpec> get_spec() const { return _spec; }
	void send_to(ostream& os) const override;


private:
	string _name;
	double _length;
	shared_ptr<const MusicSpec> _spec;
};
#endif

