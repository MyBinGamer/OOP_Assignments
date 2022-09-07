#include <iostream>
#include "Game.h"
#include "Inventory.h"
using namespace std;

// output abstraction object properties to the console window
void show(const Game & item)
{
    cout << item.get_id() << " "
        << "'" << item.get_name() << "' "
        << "'" << item.get_developer() << "' "
        << item.get_price() << " "
        //<< item.get_platform() 
    << endl;
}

// solution entry function
int main()
{
    Inventory inv;

    inv.init();

    // specify and add a least two different abstraction objects
    inv.add_item(1, "Stardew Valley", "ConcernedApe", 9.99, Game::Platform::PC);
    inv.add_item(2, "Among Us", "Innersloth", 3.29, Game::Platform::MOBILE);

    Game qry;
    // provide some querying values (some can be default (e.g., "", 0) to denote unset criteria)
    qry.init(1, "", "", 0.00, Game::Platform::ANY);

    show(inv.find_item(qry));

    // test with another query values
    qry.init(0, "", "", 3.29, Game::Platform::ANY);

    show(inv.find_item(qry));

    qry.init(0, "", "", 1.99, Game::Platform::ANY);

    show(inv.find_item(qry));

    return 0;
}