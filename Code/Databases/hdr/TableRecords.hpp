#pragma once
#include <ctime>
#include <string>
#include <ostream>
#include <vector>
#include <optional>

namespace Code::Databases
{

enum class IsItDateOrTime
{
    dateOnly,
    timeOnly,
    dateAndTime,
    unspecified
};

struct Tm : std::tm
{
	Tm();
	Tm(int year, int month, int day, int hour, int min, int sec, int daylightSave = -1);
	Tm(const std::tm& tm, IsItDateOrTime isItDateOrTime = IsItDateOrTime::unspecified);
    Tm(int year, int month, int day);
    Tm(int hour, int min, int sec, int daylightSave);

    IsItDateOrTime isItDateOrTime;
};

std::ostream& operator << (std::ostream& out, const Tm& dateAndOrTime);

struct Record1 final
{
    bool trueOrFalse {};
    char letter {};
    std::string sentence {};
    int number1 {0};
    double number2 {0.0};
};

struct Record2 final
{
    Tm dateOnly {};
    Tm timeOnly {};
    Tm dateTime {};
};

struct Record3 final
{
    std::optional<std::string> sentence {};
    std::optional<int> number1 {0};
    std::optional<double> number2 {0.0};
};

struct Record4 final
{
    Record4(const std::optional<Tm>& dateOnly, const std::optional<Tm>& timeOnly, const std::optional<Tm>& dateTime)
        : dateOnly(dateOnly)
        , timeOnly(timeOnly)
        , dateTime(dateTime)
    {}

    std::optional<Tm> dateOnly {};
    std::optional<Tm> timeOnly {};
    std::optional<Tm> dateTime {};
};

std::ostream& operator << (std::ostream& out, const Record1& record);
std::ostream& operator << (std::ostream& out, const Record2& record);
std::ostream& operator << (std::ostream& out, const Record3& record);
std::ostream& operator << (std::ostream& out, const Record4& record);

template<typename T>
std::ostream& operator << (std::ostream& out, const std::optional<T>& opt)
{
    return opt.has_value() ? out << opt.value() : out;
}

inline std::vector<Record1> seedRecords1 {
    {true, 'a', "AAaa", 1, 1.1},
    {false, 'b', "BBbb", 2, 2.2},
    {true, 'c', "CCcc", 3, 3.3},
    {false, 'd', "DDdd", 4, 4.4},
    {true, 'e', "EEee", 5, 5.5}
};

inline std::vector<Record2> seedRecords2 {
    {
        Tm {2001, 1, 11},
        Tm {1, 31, 51, -1},
        Tm {2001, 1, 11, 1, 31, 51}
    },
    {
        Tm {2002, 2, 12},
        Tm {2, 32, 52, -1},
        Tm {2002, 2, 12, 2, 32, 52}
    },
    {
        Tm {2003, 3, 13},
        Tm {3, 33, 53, -1},
        Tm {2003, 3, 13, 3, 33, 53}
    },
    {
        Tm {2004, 4, 14},
        Tm {4, 34, 54, -1},
        Tm {2004, 4, 14, 4, 34, 54}
    },
    {
        Tm {2005, 5, 15},
        Tm {5, 35, 55, -1},
        Tm {2005, 5, 15, 5, 35, 55}
    }
};

inline std::vector<Record3> seedRecords3 {
    {"Aaa",         11,             1.1},
    {"Bbb",         22,             std::nullopt},
    {"Ccc",         std::nullopt,   3.3},
    {std::nullopt,  44,             4.4},
    {"Eee",         std::nullopt,   std::nullopt},
    {std::nullopt,  66,             std::nullopt},
    {std::nullopt,   std::nullopt,  7.7},
    {std::nullopt,  std::nullopt,   std::nullopt}
};

inline std::vector<Record4> seedRecords4 {
    {
        Tm {2001, 1, 11},
        Tm {1, 31, 51, -1},
        Tm {2001, 1, 11, 1, 31, 51}
    },
    {
        Tm {2002, 2, 12},
        Tm {2, 32, 52, -1},
        std::nullopt
    },
    {
        Tm {2003, 3, 13},
        std::nullopt,
        Tm {2003, 3, 13, 3, 33, 53}
    },
    {
        std::nullopt,
        Tm {4, 34, 54, -1},
        Tm {2004, 4, 14, 4, 34, 54}
    },
    {
        Tm {2005, 5, 15},
        std::nullopt,
        std::nullopt
    },
    {
        std::nullopt,
        Tm {6, 36, 56, -1},
        std::nullopt
    },
    {
        std::nullopt,
        std::nullopt,
        Tm {2007, 7, 17, 7, 37, 57}
    }, 
    {
        std::nullopt, 
        std::nullopt,
        std::nullopt
    }
};

} // ~namespace Code::Databases
