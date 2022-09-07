#include "TodoList.h"
#include <iostream>


void TodoList::add_task(string description, Task::PRIORITY priority, DateTime due_time)
{
    Task new_task(description, priority, due_time);
    this->add_task(new_task);
}

void TodoList::add_task(Task task)
{
    if (!task.is_due()) {
        _tasks.push_back(task);
    }
}

void TodoList::complete_task(size_t i)
{
    if (!_tasks[i].is_done())
        _tasks[i].toggle_done();
}

bool TodoList::task_is_due(size_t i) const
{
    return _tasks[i].is_due();
}

void TodoList::send_to(ostream& out, function<bool(const Task&)> filter) const
{
    for (auto& task : _tasks)
        if (filter(task))
            out << (string)task << "\n";
}

bool isDone(Task t) { return t.is_done(); } //Part of Remove done tasks

void TodoList::remove_done_tasks()
{
    _tasks.erase(std::remove_if(_tasks.begin(), _tasks.end(), isDone), _tasks.end());

}