#include <iostream>
#include <iomanip>
#include "TableRecords.hpp"

namespace Code::Databases
{

Tm::Tm() 
    : std::tm{}
{}

Tm::Tm(int year, int month, int day, int hour, int min, int sec, int daylightSave)
    : std::tm{}
    , isItDateOrTime(IsItDateOrTime::dateAndTime)
{
    tm_year = year - 1900;
    tm_mon = month - 1;
    tm_mday = day;
    tm_hour = hour;
    tm_min = min;
    tm_sec = sec;
    tm_isdst = daylightSave;    // > 0 daylight saving time is in effect
                                // = 0 daylight saving time is not in effect
                                // < 0 no information about daylight saving so determine it from OS
}

Tm::Tm(const std::tm& tm, IsItDateOrTime isItDateOrTime)
    : std::tm(tm)
    , isItDateOrTime(isItDateOrTime)
{}

Tm::Tm(int year, int month, int day)
    : std::tm{}
    , isItDateOrTime(IsItDateOrTime::dateOnly)
{
    tm_year = year - 1900;
    tm_mon = month - 1;
    tm_mday = day;
}

Tm::Tm(int hour, int min, int sec, int daylightSave)
    : std::tm{}
    , isItDateOrTime(IsItDateOrTime::timeOnly)
{
    tm_year = -1900; // year 0 B.C. or 0 A.D. (only time is meant to be represented here)
    tm_mon = -1;     // Sqlite3 database displays the TIME data type with date, so let year, month, day show zeros

    tm_hour = hour;
    tm_min = min;
    tm_sec = sec;
    tm_isdst = daylightSave;    // > 0 daylight saving time is in effect
                                // = 0 daylight saving time is not in effect
                                // < 0 no information about daylight saving so determine it from OS
}

std::ostream& operator << (std::ostream& out, const Tm& dateAndOrTime)
{
    if (dateAndOrTime.isItDateOrTime == IsItDateOrTime::dateOnly)
    {
        out << std::put_time(&dateAndOrTime, "%Y/%b/%d");
    }
    else if (dateAndOrTime.isItDateOrTime == IsItDateOrTime::timeOnly)
    {
        out << std::put_time(&dateAndOrTime, "%H:%M:%S");
    }
    else if (dateAndOrTime.isItDateOrTime == IsItDateOrTime::dateAndTime)
    {
        out << std::put_time(&dateAndOrTime, "%Y/%b/%d %H:%M:%S");
    }

    return out;
}

std::ostream& operator << (std::ostream& out, const Record1& record)
{
    out << std::boolalpha << record.trueOrFalse << ", "
        << record.letter << ", "
        << record.phrase << ", "
        << record.number1 << ", "
        << record.number2;

    return out;
}

std::ostream& operator << (std::ostream& out, const Record2& record)
{
    out << std::put_time(&record.dateOnly, "%Y/%b/%d") << ", "
        << std::put_time(&record.timeOnly, "%H:%M:%S") << ", "
        << std::put_time(&record.dateTime, "%Y/%b/%d %H:%M:%S");

    return out;
}

std::ostream& operator << (std::ostream& out, const Record3& record)
{
    if (record.phrase.has_value())
        out << record.phrase.value() << ", ";

    if (record.number1.has_value())
        out << record.number1.value() << ", ";

    if (record.number2.has_value())
        out << record.number2.value();

    return out;
}

std::ostream& operator << (std::ostream& out, const Record4& record)
{
    if (record.dateOnly.has_value())
        out << record.dateOnly.value() << ", ";

    if (record.timeOnly.has_value())
        out << record.timeOnly.value() << ", ";

    if (record.dateTime.has_value())
        out << record.dateTime.value();

    return out;
}

} // ~namespace Code::Databases
