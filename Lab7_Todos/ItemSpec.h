#pragma once
#include <ostream>
using namespace std;

class ItemSpec {
public:
	ItemSpec() = default;
	virtual ~ItemSpec() = default;
	virtual void send_to(ostream& os) const = 0;
	virtual bool matches(const ItemSpec & itemSpec) const = 0;
};
ostream& operator<<(ostream& os, const ItemSpec& spec);