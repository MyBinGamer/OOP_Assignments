#include "ItemSpec.h"

ostream& operator<<(ostream& os, const ItemSpec& spec) {
	spec.send_to(os);
	return os;
}