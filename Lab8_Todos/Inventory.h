#pragma once
#ifndef INVENTORY
#define INVENTORY

#include "Game.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Inventory
{
public:
    // Returns the number of currently stored abstraction objects
    size_t get_count() const { return _items.size(); }

    const Game& operator[](size_t i) const { return get_item(i); }

    // Returns stored abstraction object by its index or default if index is invalid
    const Game& get_item(size_t i) const {
        try {
            if (i < _items.size()) {
                return _items[i];
            }
            throw out_of_range("Invalid index value.");
        }
        catch (out_of_range& oor) {
            cerr << "You got an error: " << oor.what() << endl;
            terminate();
        }
    }

    void add_item(const Game & new_item);
    // Looks for a matching abstraction object and returns the first found or default object
    Game find_item(const Game& query) const;

    Game find_item(const GameSpec& spec_query) const;

    vector<Game> find_all_items(const GameSpec& otherSpec) const;

    void save(const string& csv_file_name) const;
    void load(const string& csv_file_name);

    vector<Game>::const_iterator begin() const { return _items.begin(); }
    vector<Game>::const_iterator end() const { return _items.end(); }

private:
    // An array for storing abstraction objects
    vector<Game> _items;
};

#endif
