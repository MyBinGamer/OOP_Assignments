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
        << "'" << item.get_developer() << "' "
        << item.get_price() << " "
        << PLATFORM_S[(size_t)item.get_platform()] //C++ idiom
        << endl;
}

Game max_price(const Inventory & inv) 
{
    Game item_list[10]; // 10 is max size

    int n = inv.get_count(); //number of elements in inventory
    for (int i = 0; i < n; i++) {
        item_list[i] = inv.get_item(i);
    }

    Game _item = item_list[0]; //default item which might change later

    for (int i = 1; i < n; i++) {
        if (item_list[i].get_price() > _item.get_price()) {
            _item = item_list[i]; //If price of "i" item is bigger => "i" item is current max 
        }
    }
    return _item;
}

double avg_price(const Inventory & inv) {
    double price_list[10]; // 10 is max size
    int n = inv.get_count(); // number of elements in inventory
    for (int i = 0; i < n; i++) {
        price_list[i] = inv.get_item(i).get_price(); //we are making array with price elements so it will be easier to calculate average price
    }
    double sum = 0;
    return accumulate(price_list, price_list + n, sum) / n; //accumulate from numeric which sums all values in array. At the end i divide it by n(count of inv) to get average value

}
// solution entry function
int main()
{
    Inventory inv;

    inv.init();

    // specify and add a least two different abstraction objects

    inv.add_item(1, "Stardew Valley", "ConcernedApe", 9.99, Game::Platform::PC);

    assert(inv.get_count() == 1);

    inv.add_item(2, "Among Us", "Innersloth", 3.29, Game::Platform::MOBILE);

    assert(inv.get_count() == 2);

    inv.add_item(3, "Animal Crossing", "Monolith Soft", 59.99, Game::Platform::NINTENDO);

    inv.add_item(4, "Detroit: Become Human", "Quantic Dream", 19.99, Game::Platform::PLAYSTATION);

    inv.add_item(5, "Cyberpunk 2077", "CD Projekt Red", 29.99, Game::Platform::PC);

    assert(inv.get_count() == 5);

    inv.add_item(4, "Detroit: Become Human", "Quantic Dream", 19.99, Game::Platform::PLAYSTATION);

    assert(inv.get_count() == 5); // Identical object is not addedd to inventory list

    Game qry;

    qry.init(1, "", "", 0.00, Game::Platform::ANY); //Search by id

    assert(inv.find_item(qry).get_name() == "Stardew Valley");

    show(inv.find_item(qry));

    // test with another query values
    qry.init(2, "Among Us", "Innersloth", 3.29, Game::Platform::MOBILE); //Search by every parameter

    assert(inv.find_item(qry).get_developer() == "Innersloth");

    show(inv.find_item(qry));

    qry.init(0, "Animal Crossing", "Monolith Soft", 0, Game::Platform::ANY); //Search by 2 parameters : name and dev

    assert(inv.find_item(qry).get_id() == 3);

    show(inv.find_item(qry));

    qry.init(4, "", "Quantic Dream", 19.99, Game::Platform::ANY); //Search by 3 parameters: id, dev and price

    assert(inv.find_item(qry).get_platform() == Game::Platform::PLAYSTATION);

    show(inv.find_item(qry));

    qry.init(5, "", "", 0, Game::Platform::PC); //Search by enum class type PC and id

    assert(inv.find_item(qry).get_price() == 29.99);

    show(inv.find_item(qry));

    qry.init(0, "", "", 0, Game::Platform::XBOX); //Game with platform XBOX does't exist so it will be default item

    assert(inv.find_item(qry).get_price() == 0);

    show(inv.find_item(qry));

    cout << "The most expensive game:\n";
    show(max_price(inv));
    cout << "Average Game price: "
        << avg_price(inv)
        << "\n";
    return 0;
}