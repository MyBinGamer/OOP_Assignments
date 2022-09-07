#include <sstream>
#include "Task.h"

Task::Task(string descr, PRIORITY priority, DateTime due_date)
    : _descr{ descr }, _priority{ priority }, _due_date{ due_date }, _done{ false }
{ }

bool Task::is_done() const
{
    return _done;
}

void Task::toggle_done()
{
    _done = !_done;
}

bool Task::is_due() const
{
    return !_done && (_due_date - DateTime::today() <= 0.0);
}

Task::operator string() const
{
    // String representations of Task::PRIORITY values:
    static const char* PRIORITY_S[]{ "Low", "Normal", "High" };
    ostringstream str;

    str << "Subject: " << _descr << "\n"
        << "Priority: " << PRIORITY_S[static_cast<size_t>(_priority)] << "\n"
        << "Due date: " << (string)_due_date << "\n"
        << std::boolalpha
        << "Due? " << is_due() << "\n"
        << "Done? " << is_done() << "\n";

    return str.str();
}