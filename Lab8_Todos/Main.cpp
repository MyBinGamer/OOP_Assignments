#include <iostream>
#include "Game.h"
#include "Inventory.h"
#include <numeric>
#include <cassert>
#include <algorithm>
using namespace std;

template<typename T>

// output abstraction object properties to the console window
void show(const T & item)
{
    cout << item << "\n";
}

bool is_less(const Game& item1, const Game& item2) {
    return item1.get_price() < item2.get_price();
}

Game max_price(const Inventory& inv)
{
    if (inv.begin() == inv.end())
        throw range_error("Inventory is empty");

    return *max_element(inv.begin(), inv.end(), is_less);
}

class Average {
public:
    Average() : _sum{ 0.0 }, _count{ 0 }{}
    void operator()(const Game& item) {
        _sum += item.get_price();
        _count++;
    }
    double result() const { return _count ? _sum / _count : 0.0; }

private:
    double _sum;
    size_t _count;
};

double avg_price(const Inventory& inv) {
    return for_each(inv.begin(), inv.end(), Average()).result();
}
void show_all(const Inventory& inv) {
    for_each(inv.begin(), inv.end(), show<Game>);
}

// solution entry function
int main()
{
    try {
        Inventory inv;
        auto spc_1{ make_shared<GameSpec>("7th Beat Games",GameSpec::Platform::PC) };
        Game game_1(1, "A Dance Of Fire And Ice", 3.99, spc_1);
        Game game_2(2, "Rhythm Doctor", 8.09, spc_1);

        inv.add_item(game_1);
        inv.add_item(game_2);

        assert(inv.get_count() == 2);

        //Constructing and using shared specification
        auto spc_2{ make_shared<GameSpec>("Terry Cavanagh",GameSpec::Platform::PC) }; //Another developer with a few games on PC
        Game game_3(3, "Dicey Dungeons", 8.49, spc_2);
        Game game_4(4, "Super Hexagon", 1.99, spc_2);
        Game game_5(5, "VVVVVV", 2.99, spc_2);

        inv.add_item(game_3);
        inv.add_item(game_4);
        inv.add_item(game_5);

        assert(inv.get_count() == 5);

        show_all(inv);

        cout << "The most expensive game:\n";
        show(max_price(inv));
        cout << "Average Game price: "
            << avg_price(inv)
            << "\n";
        //save all current items to file
        auto inv_file_name{ "inventory.csv" };
        inv.save(inv_file_name);

        Inventory inv2;
        inv2.load(inv_file_name);
        cout << "Inventory2(loaded from file) have: " << inv2.get_count() << " items: " << endl;
        show_all(inv2);
    }
    catch (...) {
        cerr << "Unexpected error" << endl;
        terminate();
    }
    return 0;
}