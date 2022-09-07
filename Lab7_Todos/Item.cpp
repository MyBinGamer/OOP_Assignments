#include "Item.h"

ostream& operator<<(ostream& os, const Item& item)
{
    item.send_to(os);
    return os;
}