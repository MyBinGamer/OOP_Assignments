#include "Inventory.h"

void Inventory::add_item(shared_ptr<Item> newItem) {
    if (_count < Inventory::MAX_SIZE) {
        if (newItem->get_id() != find_item(*newItem->get_spec()).get_id()) {
            _items[_count] = newItem;
            _count++;
        }
    }
}

const Item& Inventory::find_item(const ItemSpec& otherSpec) const {
    for (size_t i{ 0U }; i < _count; i++)
        if (_items[i]->get_spec()->matches(otherSpec))
            return *_items[i]; // return the first object with matching specification

    static const Item def{};
    return def; // return the 'default' value object
}

void Inventory::save(const string& csv_file_name) const {
    ofstream ofs(csv_file_name);
    if (ofs)
        for (size_t i{ 0 }; i < get_count(); i++)
            ofs << *_items[i] << "\n";
    ofs.close();
    cout << "Saved...\n";
}
