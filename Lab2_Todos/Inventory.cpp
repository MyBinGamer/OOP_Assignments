#include "Inventory.h"

// The parameters must match with the class declaration
void Inventory::add_item(int id, const string name, const string developer, double price, const Game::Platform & platform)
{
    if (_count < Inventory::MAX_SIZE)
    {
        Game new_item;
        new_item.init(id, name, developer, price, platform);
        _items[_count] = new_item;
        _count++;
    }
}

Game Inventory::find_item(const Game & query) const
{
    for (size_t i = 0; i < _count; i++)
    {
        // for integer and boolean type property
        if (query.get_id() != 0
            && query.get_id() != _items[i].get_id())
            continue;

        constexpr double epsil{ 0.005 };
        if (query.get_price() != 0.0
            && (epsil < abs(query.get_price() - _items[i].get_price())))
            continue;

        // for string type property
        if (query.get_name() != ""
            && query.get_name() != _items[i].get_name())
            continue;

        if (query.get_developer() != ""
            && query.get_name() != _items[i].get_name())
            continue;

        return _items[i];
    }

    return Game{}; // return the 'default' object
}