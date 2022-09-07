#include "Inventory.h"

// The parameters must match with the class declaration
void Inventory::add_item(const Game & new_item)
{
    auto found{ this->find_all_items(*new_item.get_spec()) };

    for (auto found_item : found)
        if (found_item.get_id() == new_item.get_id())
            return;

    _items.push_back(new_item);
}

Game Inventory::find_item(const Game& query) const
{
    for (size_t i = 0; i < _items.size(); i++)
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

        if (!_items[i].get_spec()->matches(*query.get_spec()))
            continue;

        return _items[i];
    }

    return Game{}; // return the 'default' object
}

Game Inventory::find_item(const GameSpec& otherSpec) const {
    auto found{ this->find_all_items(otherSpec) };

    if (!found.empty())
        return found[0];// return the first object with a matching specification

    return Game{}; //return the default value object
}

void Inventory::save(const string& csv_file_name) const {
    ofstream ofs(csv_file_name);
    if (ofs)
        for (size_t i{ 0 }; i < get_count(); i++)
            ofs << _items[i] << "\n";
    ofs.close();
    cout << "Saved...\n";
}

void Inventory::load(const string& csv_file_name) {
    ifstream ifs(csv_file_name);
    if (!ifs) {
        cerr << "Cannot open file " << csv_file_name << "!" << endl;
        return;
    }
    string line;
    Game obj;
    while (getline(ifs, line)) {
        istringstream item_line{ line };
        item_line >> obj;
        _items.push_back(obj);
    }
    ifs.close();
}

vector<Game> Inventory::find_all_items(const GameSpec& otherSpec) const {
    vector<Game> found;

    for (auto item : _items)
        if (item.get_spec()->matches(otherSpec))
            found.push_back(item);

    return found; // If there are no matches, then empty container object is returned.
}