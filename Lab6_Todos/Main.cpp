#include <iostream>
#include "Game.h"
#include "Inventory.h"
#include <numeric>
#include <cassert>
using namespace std;

// output abstraction object properties to the console window
void show(const Game& item)
{
    cout << item << "\n";
}

Game max_price(const Inventory& inv)
{
    try{
        size_t n = inv.get_count(); //number of elements in inventory
        if (n != 0) {
            size_t max_price_pos = 0;
            for (size_t i = 1; i < n; i++) {
                if (inv.get_item(i).get_price() > inv.get_item(max_price_pos).get_price()) {
                    max_price_pos = i; //If price of "i" item is bigger = > "i" is current max position
                }
            }
            return inv.get_item(max_price_pos);//return game object with highest price
        }
        throw logic_error("Inventory without items");
    }
    catch (logic_error& le) {
        cerr << "You have got an error: " << le.what() << endl;
        terminate();
    }
}

double avg_price(const Inventory& inv) {
    try {
        size_t n = inv.get_count(); // number of elements in inventory
        if (n != 0) {
            double sum = 0; // this var will be sum of all prices
            for (size_t i = 0; i < n; i++) {
                sum += inv.get_item(i).get_price(); //it is the same as sum = sum + price of each game item
            }
            return sum / n; // average value
        }
        throw logic_error("Empty Inventory");
    }
    catch (logic_error & le) {
        cerr << "You have got an error: " << le.what() << endl;
        terminate();
    }
}
// solution entry function
int main()
{
    try {
        Inventory inv;
        auto spc_1{ make_shared<GameSpec>(GameSpec::Platform::PC, "7th Beat Games") };
        inv.add_item(1, "A Dance Of Fire And Ice", 3.99, spc_1);
        inv.add_item(2, "Rhythm Doctor", 8.09, spc_1);

        assert(inv.get_count() == 2);

        show(inv[0]);
        show(inv[1]);

        //Constructing and using shared specification
        auto spc_2{ make_shared<GameSpec>(GameSpec::Platform::PC, "Terry Cavanagh") }; //Another developer with a few games on PC
        inv.add_item(3, "Dicey Dungeons", 8.49, spc_2);
        inv.add_item(4, "Super Hexagon", 1.99, spc_2);
        inv.add_item(5, "VVVVVV", 2.99, spc_2);

        assert(inv.get_count() == 5);

        show(inv[2]);
        show(inv[3]);
        show(inv[4]);
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
        cout << "Inventory2(loaded from file) have: " << inv2.get_count() << " items" << endl;

        //I commented lines which trigger try-catch statements below
        //inv.add_item(5, "VVVVVV", 2.99, spc_2); //item is already in inv
        //inv.add_item(6, "Random", -9.25, spc_1); // negative price
        //inv.add_item(6, "", 3.21, spc_1); //empty name
        //show(inv.get_item(6)); //or 
        //show(inv[6]); // Out of range
        //max_price(Inventory{}); // empty inv
        //avg_price(Inventory{}); // empty inv
    }
    catch (...) {
        cerr << "Unexpected error" << endl;
        terminate();
    }
    return 0;
}