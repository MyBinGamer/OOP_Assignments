#ifndef TodoList_h
#define TodoList_h

#include <ostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "Task.h"
#include "DateTime.h"

using namespace std;

class TodoList
{
public:
    void add_task(string description, Task::PRIORITY priority, DateTime due_time);
    void add_task(Task task);
    void complete_task(size_t i);
    bool task_is_due(size_t i) const;
    void send_to(ostream& out, function<bool(const Task&)> filter = [](const Task&) { return true; }) const;
    size_t get_tasks_count() const { return _tasks.size(); }
    void remove_done_tasks();

private:
    vector<Task> _tasks;
};

#endif