#pragma once
#include <memory>
#include <ostream>
#include "ItemSpec.h"

using namespace std;
class Item
{
public:
	Item() = default;
	virtual ~Item() = default;
	Item(int id, shared_ptr<const ItemSpec> spec) : _id{ id } { set_spec(spec);}

	int get_id() const { return _id; }

	shared_ptr<const ItemSpec> get_spec() const { return _spec; }

	virtual void send_to(ostream& os) const { 
		os << _id <<";";
		if (_spec)
			_spec->send_to(os);
	}

protected:
	// for changing the specification only in this and in derived classes:
	void set_spec(shared_ptr<const ItemSpec> spec)
	{
		_spec = spec;
	}

private:
	int _id;
	shared_ptr<const ItemSpec> _spec;
};

ostream& operator<<(ostream& os, const Item& item);