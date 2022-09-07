#include <iostream>   // to use objects cout and cin
#include <cassert>    // to use function assert()
#include "Task.h"     // to use Task class
#include "TodoList.h" // to use TodoList class
#include "DateTime.h" // to use DateTime class

using namespace std;

int main()
{
    TodoList todos;

    DateTime test_date_time{ DateTime::today() };

    test_date_time += 1; // tomorrow

    todos.add_task("Buy a milk", Task::PRIORITY::NORMAL, test_date_time);
    assert(1 == todos.get_tasks_count());

    test_date_time -= 2; // yesterday

    Task bread("Buy a bread", Task::PRIORITY::HIGH, test_date_time);
    todos.add_task(bread);
    assert(1 == todos.get_tasks_count()); // We didn't add this task because its time passed

    // Shows all tasks
    cout << "All tasks\n====================\n";
    todos.send_to(cout);

    // Shows due tasks only
    cout << "Due tasks\n====================\n";

    auto is_due = [&](const Task& t) { return t.is_due(); };
    todos.send_to(std::cout, is_due);

    cout << "Completing 1st task ...\n";
    todos.complete_task(0);
    assert(!todos.task_is_due(0));

    cout << "Due tasks\n====================\n";
    todos.send_to(std::cout, is_due);
    // Removes done tasks
    todos.remove_done_tasks();
    assert(0 == todos.get_tasks_count()); // We should have empty list cause we don't have any more tasks to complete
    cout << "\nAll done tasks are removed successfully \n";

#ifndef NDEBUG
    // Uncomment the next two lines to pause before the program exits:
    cout << "\nPress Enter to exit";
    cin.get(); // wait for the Enter key
#endif

    return 0;
}