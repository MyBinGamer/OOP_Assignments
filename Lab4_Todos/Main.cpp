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
        << "'" << item.get_spec().get_developer() << "' "
        << item.get_price() << " "
        << PLATFORM_S[(size_t)item.get_spec().get_platform()] //C++ idiom
        << endl;
}

Game max_price(const Inventory& inv)
{
    int n = inv.get_count(); //number of elements in inventory
    if (n != 0)
    {
        int max_price_pos = 0;
        for (int i = 1; i < n; i++) {
            if (inv.get_item(i).get_price() > inv.get_item(max_price_pos).get_price()) {
                max_price_pos = i; //If price of "i" item is bigger = > "i" is current max position
            }
        }
    return inv.get_item(max_price_pos); //return game object with highest price
    }
    return Game{}; //if inv is empty we reutrn default Game object

}

double avg_price(const Inventory& inv) {
    int n = inv.get_count(); // number of elements in inventory
    double sum = 0; // this var will be sum of all prices
    for (int i = 0; i < n; i++) {
        sum +=inv.get_item(i).get_price(); //it is the same as sum = sum + price of each game item
    }
    return sum / n; // average value

}
// solution entry function
int main()
{
    Inventory inv;
    GameSpec spc(GameSpec::Platform::PC, "7th Beat Games"); //This Developer made a few games on PC. For example:
    inv.add_item(1, "A Dance Of Fire And Ice", 3.99, spc);

    assert(inv.get_count() == 1);

    inv.add_item(2, "Rhythm Doctor", 8.09, spc);

    assert(inv.get_count() == 2);

    Game qry;

    show(inv.find_item(qry)); //It will return default game object which differs from spc

    show(inv.find_item(spc));

    Game qry1(0, "", 0.00, spc);

    show(inv.find_item(qry1)); //It will return the same object as find_item(spc)

    show(inv.find_item(spc));

    Game qry2(2, "", 0.00, spc);

    show(inv.find_item(qry2)); //Here, spc is the same but id is 2 so it will return different object

    show(inv.find_item(spc));

    cout << "The most expensive game:\n";
    show(max_price(inv));
    cout << "Average Game price: "
        << avg_price(inv)
        << "\n";
    return 0;
}