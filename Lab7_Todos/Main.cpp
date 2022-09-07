#include <iostream>
#include "Game.h"
#include "Music.h"
#include "Inventory.h"
#include <numeric>
#include <cassert>
using namespace std;

// output abstraction object properties to the console window
void show(const Item & item)
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
                auto temp1{ dynamic_cast<const Game*>(&inv.get_item(i)) };
                auto temp2{ dynamic_cast<const Game*>(&inv.get_item(max_price_pos)) };
                if ((nullptr != temp1) && (nullptr != temp2)) {
                    const Game& tempGame{ *temp1 };
                    const Game& tempMaxGame{ *temp2 };
                    if (tempGame.get_price() > tempMaxGame.get_price()) {
                        max_price_pos = i; //If price of "i" item is bigger = > "i" is current max position
                    }
                }
            }
            auto temp3{ dynamic_cast<const Game*>(&inv.get_item(max_price_pos)) };
            if (nullptr != temp3) {
                const Game& tempRGame{ *temp3 };
                return tempRGame;//return game object with highest price
            }
            else {
                throw logic_error("Inventory don't contain any Game items");
            }
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
        size_t n = inv.get_count(); // number of all elements in inventory
        if (n != 0) {
            double sum = 0; // this var will be sum of all prices
            size_t idx = 0; //number of game items in our inv
            for (size_t i = 0; i < n; i++) {
                auto temp{ dynamic_cast<const Game*>(&inv.get_item(i)) };
                if (nullptr != temp) {
                    idx++;
                    const Game& tempGame{ *temp };
                    sum += tempGame.get_price(); //it is the same as sum = sum + price of each game item
                }
            }
            return sum / idx; // average value
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
        auto game1{ make_shared<Game>(1,"A Dance Of Fire And Ice", 3.99, spc_1) };
        auto game2{ make_shared<Game>(2, "Rhythm Doctor", 8.99, spc_1) };
        inv.add_item(game1);
        inv.add_item(game2);
        auto mscp_1{ make_shared<MusicSpec>("Shirobon", "Dimensions", 2016, MusicSpec::Genre::ELECTRO) };
        auto music1{ make_shared<Music>(3, mscp_1, "On The Run", 4.28) };
        auto music2{ make_shared<Music>(4, mscp_1, "FOX", 5.16) };
        auto music3{ make_shared<Music>(5, mscp_1, "Out of Love", 4.42) };
        inv.add_item(music1);
        inv.add_item(music2);
        inv.add_item(music3);

        assert(inv.get_count() == 5);

        show(inv[0]);
        show(inv[1]);
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
    }
    catch (...) {
        cerr << "Unexpected error" << endl;
        terminate();
    }
    return 0;
}