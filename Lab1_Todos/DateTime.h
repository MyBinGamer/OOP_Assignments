#pragma once

#ifndef DateTime_h
#define DateTime_h

#include <ctime>
#include <string>

#ifndef _MSC_VER
#include <cstring>
#endif

/// A simple C++ Standard Library std::time_t wrapper class
class DateTime
{
public:
    static DateTime today()
    {
        return DateTime(time(nullptr)); // today
    }

    DateTime()
        : _datetime(0) {}

    DateTime(std::time_t datetime)
        : _datetime(datetime) {}

    DateTime(unsigned due_year, unsigned due_month, unsigned due_day, unsigned due_hour, unsigned due_minute)
    {
        tm tmp_tm{};

        tmp_tm.tm_year = due_year >= 1000 ? due_year - 1900 : due_year;
        tmp_tm.tm_mon = due_month - 1;
        tmp_tm.tm_mday = due_day;
        tmp_tm.tm_hour = due_hour;
        tmp_tm.tm_min = due_minute;
        _datetime = mktime(&tmp_tm);
    }

    DateTime(const DateTime& dt)
    {
        _datetime = dt._datetime;
    }

    operator std::time_t() const
    {
        return _datetime;
    };

    operator std::string() const
    {
        tm time;
        char time_str[32];
        bool unknown_time{ false };

#ifdef _MSC_VER
        if (EINVAL == localtime_s(&time, &_datetime))
#else
        time = *localtime(&_datetime);
        if (false)
            //if (nullptr == localtime_r(&_datetime, &time))
#endif
            unknown_time = true;
        else if (0 == strftime(time_str, sizeof(time_str), "%c", &time))
            unknown_time = true;

        if (unknown_time)
#ifdef _MSC_VER
            strcpy_s(time_str, sizeof(time_str), "unknown");
#else
            strcpy(time_str, "unknown");
#endif
        return time_str;
    }

    DateTime operator+=(int days)
    {
        tm tmp_tm;

#ifdef _MSC_VER
        if (EINVAL != localtime_s(&tmp_tm, &_datetime))
#else
        tmp_tm = *localtime(&_datetime);
        //if (nullptr != localtime_r(&_datetime, &tmp_tm))
#endif
        {
            tmp_tm.tm_mday += days;
            _datetime = mktime(&tmp_tm);
        }
        return *this;
    }

    DateTime operator-=(int days)
    {
        return (*this += -days);
    }

    double operator-(const DateTime& other)
    {
        return difftime(_datetime, other);
    }

private:
    std::time_t _datetime;
};

#endif