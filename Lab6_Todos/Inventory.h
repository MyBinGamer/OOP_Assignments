#pragma once
#ifndef INVENTORY
#define INVENTORY

#include "Game.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>

class Inventory
{
public:
    
    // Initializes the inventory for storing abstraction objects
    Inventory() : _count{ 0U } {}

    // Returns the number of currently stored abstraction objects
    size_t get_count() const { return _count; }

    const Game & operator[](size_t i) const { return get_item(i); }

    // Returns stored abstraction object by its index or default if index is invalid
    const Game & get_item(size_t i) const {
        try {
            if (i < _count) {
                return _items[i];
            }
            throw out_of_range("Invalid index value.");
        }
        catch (out_of_range& oor) {
            cerr << "You got an error: " << oor.what() << endl;
            terminate();
        }
    }

    // From passed property values, creates and adds new abstraction object in an array _items
    void add_item(int id, const string name, double price, shared_ptr<const GameSpec> spec);
    // Looks for a matching abstraction object and returns the first found or default object
    Game find_item(const Game& query) const;

    Game find_item(const GameSpec& spec_query) const;

    void save(const string& csv_file_name) const;
    void load(const string& csv_file_name);

private:
    // The maximum number of abstraction objects that can be stored
    static const size_t MAX_SIZE{ 10 };

    // An array for storing abstraction objects
    Game _items[Inventory::MAX_SIZE];

    // The number of currently stored abstraction objects in the array _items
    size_t _count;
};

#endif