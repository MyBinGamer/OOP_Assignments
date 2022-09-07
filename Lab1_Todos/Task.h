#pragma once
#ifndef Task_h
#define Task_h

#include <string>
#include "DateTime.h"

using namespace std;

class Task
{
public:
    enum class PRIORITY { LOW, NORMAL, HIGH };
    Task(string descr, PRIORITY priority, DateTime due_date);
    bool is_done() const;
    void toggle_done();
    bool is_due() const;
    operator string() const;

private:
    string   _descr;
    PRIORITY _priority;
    DateTime _due_date;
    bool     _done;
};

#endif
