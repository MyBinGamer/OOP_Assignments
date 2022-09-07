#include "Inventory.h"

// The parameters must match with the class declaration
void Inventory::add_item(int id, string name, double price, shared_ptr<const GameSpec> spec)
{
    try {
        if (id <= 0) {
            throw logic_error("Invalid value of id!");
        }
        if (name.empty()) {
            throw logic_error("Name is empty");
        }
        if (price <= 0.0) {
            throw logic_error("Input price is invalid");
        }
        if (spec == nullptr) {
            throw logic_error("Spec is invalid");
        }
        if (_count < Inventory::MAX_SIZE)
        {
            Game new_item(id, name, price, spec);
            Game f_item = find_item(new_item); //found item or default
            if ((f_item.get_id() != id)
                || (f_item.get_spec()->get_developer() != spec->get_developer())
                || (f_item.get_name() != name)
                || (f_item.get_price() != price)
                || (f_item.get_spec()->get_platform() != spec->get_platform())) {
                _items[_count] = new_item;
                _count++;
            }
            else {
                throw logic_error("The item you add already exists in this inventory");
            }
        }
    }
    catch(logic_error & le){
        cerr << "You have got an error: " << le.what() << endl;
        terminate();
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

        if (!_items[i].get_spec()->matches(*query.get_spec()))
            continue;

        return _items[i];
    }

    return Game{}; // return the 'default' object
}

Game Inventory::find_item(const GameSpec& otherSpec) const {

    for (size_t i = 0; i < _count; i++)
        if (!_items[i].get_spec()->matches(otherSpec))
            return _items[i]; // return the first object with a matching specification

    return Game{}; //return the default value
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
    size_t line_count{};
    while (getline(ifs, line)) {
        istringstream item_line{ line };
        item_line >> _items[line_count];
        ++line_count;
    }
    _count = line_count;
    ifs.close();
}