#include "Inventory.h"

// The parameters must match with the class declaration
void Inventory::add_item(int id, const string& name, double price, const GameSpec & spec)
{
    if (_count < Inventory::MAX_SIZE)
    {
        Game new_item(id, name, price, spec);
        Game f_item = find_item(new_item); //found item or default
        if ((f_item.get_id() != id)
            || (f_item.get_spec().get_developer() != spec.get_developer())
            || (f_item.get_name() != name)
            || (f_item.get_price() != price)
            || (f_item.get_spec().get_platform() != spec.get_platform())) {
            _items[_count] = new_item;
            _count++;
        }
    }
}

Game Inventory::find_item(const Game& query) const
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

        if (query.get_spec().get_developer() != ""
            && query.get_spec().get_developer() != _items[i].get_spec().get_developer())
            continue;

        //For enum class types. Just did it for myself
        if (query.get_spec().get_platform() != GameSpec::Platform::ANY
            && query.get_spec().get_platform() != _items[i].get_spec().get_platform())
            continue;

        return _items[i];
    }

    return Game{}; // return the 'default' object
}

Game Inventory::find_item(const GameSpec& spec_query) const {

    for (size_t i = 0; i < _count; i++)
    {
        if (spec_query.get_developer() != ""
            && spec_query.get_developer() != _items[i].get_spec().get_developer())
            continue;

        if (spec_query.get_platform() != GameSpec::Platform::ANY
            && spec_query.get_platform() != _items[i].get_spec().get_platform())
            continue;

        return _items[i];
    }

    return Game{}; //return the default value
}