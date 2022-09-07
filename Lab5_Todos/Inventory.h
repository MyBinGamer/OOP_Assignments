#pragma once
#ifndef INVENTORY
#define INVENTORY

#include "Game.h" // must be replaced, e.g. to "Bicycle"

class Inventory
{
public:

    Inventory() : _count{ 0U } {}

    // Initializes the inventory for storing abstraction objects
    //void init() { _count = 0; }

    // Returns the number of currently stored abstraction objects
    size_t get_count() const { return _count; }

    // Returns stored abstraction object by its index or default if index is invalid
    Game get_item(size_t i) const { return (i < _count) ? _items[i] : Game{}; }

    // From passed property values, creates and adds new abstraction object in an array _items
    // (replace parameters to match your property types and identifiers)
    //void add_item(int id, const string & name, const string& developer, double price, const Game::Platform& platform);
    void add_item(int id, const string& name, double price, shared_ptr<const GameSpec> spec);
    // Looks for a matching abstraction object and returns the first found or default object
    Game find_item(const Game& query) const;

    Game find_item(const GameSpec& spec_query) const;

private:
    // The maximum number of abstraction objects that can be stored
    static const size_t MAX_SIZE{ 10 };

    // An array for storing abstraction objects
    Game _items[Inventory::MAX_SIZE];

    // The number of currently stored abstraction objects in the array _items
    size_t _count;
};

#endif