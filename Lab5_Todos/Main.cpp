#include <iostream>
#include "Game.h"
#include "Inventory.h"
#include <numeric>
#include <cassert>
using namespace std;

// output abstraction object properties to the console window
void show(const Game& item)
{
    static const char* PLATFORM_S[]{ "ANY" , "PC" , "XBOX" , "PLAYSTATION" , "NINTENDO" , "MOBILE" };
    cout << item.get_id() << " "
        << "'" << item.get_name() << "' "
        << item.get_price() << " ";

        auto is_ptr{ item.get_spec() };
        if (is_ptr) {
            cout << "'" << is_ptr->get_developer() << "' "
                << PLATFORM_S[(size_t)is_ptr->get_platform()] //C++ idiom
                << endl;
        }
}

Game max_price(const Inventory& inv)
{
    size_t n = inv.get_count(); //number of elements in inventory
    if (n != 0)
    {
        size_t max_price_pos = 0;
        for (size_t i = 1; i < n; i++) {
            if (inv.get_item(i).get_price() > inv.get_item(max_price_pos).get_price()) {
                max_price_pos = i; //If price of "i" item is bigger = > "i" is current max position
            }
        }
        return inv.get_item(max_price_pos); //return game object with highest price
    }
    return Game{}; //if inv is empty we reutrn default Game object

}

double avg_price(const Inventory& inv) {
    size_t n = inv.get_count(); // number of elements in inventory
    double sum = 0; // this var will be sum of all prices
    for (size_t i = 0; i < n; i++) {
        sum += inv.get_item(i).get_price(); //it is the same as sum = sum + price of each game item
    }
    return sum / n; // average value

}
// solution entry function
int main()
{
    Inventory inv;
    auto spc_1{ make_shared<GameSpec>(GameSpec::Platform::PC, "7th Beat Games") };
    inv.add_item(1, "A Dance Of Fire And Ice", 3.99, spc_1);
    inv.add_item(2, "Rhythm Doctor", 8.09, spc_1);

    assert(inv.get_count() == 2);

    show(inv.get_item(0));
    show(inv.get_item(1));
    
    //Constructing and using shared specification
    auto spc_2{ make_shared<GameSpec>(GameSpec::Platform::PC, "Terry Cavanagh") }; //Another developer with a few games on PC
    inv.add_item(3, "Dicey Dungeons", 8.49, spc_2);
    inv.add_item(4, "Super Hexagon", 1.99, spc_2);
    inv.add_item(5, "VVVVVV", 2.99, spc_2);

    assert(inv.get_count() == 5);

    show(inv.get_item(2));
    show(inv.get_item(3));
    show(inv.get_item(4));

    cout << "The most expensive game:\n";
    show(max_price(inv));
    cout << "Average Game price: "
        << avg_price(inv)
        << "\n";
    return 0;
}