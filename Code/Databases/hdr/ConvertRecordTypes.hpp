#include <soci/soci.h>
#include "TableRecords.hpp"

namespace Code::Databases
{

bool GetIsPostgreSql();

} // ~namespace Code::Databases

// This SOCI boiler plate MUST BE in namespace soci
namespace soci
{

template<> 
struct type_conversion<Code::Databases::Record1>
{
    typedef values base_type;

    static void from_base(values const& v, indicator /* ind */, Code::Databases::Record1& record)
    {
        record.trueOrFalse = v.get<int>("true_or_false");
        record.letter = *(v.get<std::string>("letter").data()); // string converted to char
        record.phrase = v.get<std::string>("phrase");
        record.number1 = v.get<int>("number1");
        record.number2 = v.get<double>("number2");
    }

    static void to_base(const Code::Databases::Record1& record, values& v, indicator& ind)
    {
        v.set("true_or_false", static_cast<int>(record.trueOrFalse));
        v.set("letter", record.letter);
        v.set("phrase", record.phrase);
        v.set("number1", record.number1);
        v.set("number2", record.number2);

        ind = i_ok;
    }
};

// template<> 
// struct type_conversion<Code::Databases::Record2>
// {
//     typedef values base_type;

//     static void from_base(values const& v, indicator /* ind */, Code::Databases::Record2& record)
//     {
//         record.dateOnly = v.get<std::tm>("date_only");
//         record.timeOnly = v.get<std::tm>("time_only");
//         record.dateTime = v.get<std::tm>("date_time");
//     }

//     static void to_base(const Code::Databases::Record2& record, values& v, indicator& ind)
//     {
//         if (Code::Databases::GetIsPostgreSql())
//         {
//             std::stringstream ssTimeOnly;
//             ssTimeOnly << std::put_time(&record.timeOnly, "%H:%M:%S");
//             v.set("time_only", ssTimeOnly.str());
//         }
//         else
//         {
//             v.set("time_only", static_cast<std::tm>(record.timeOnly));
//         }

//         v.set("date_only", static_cast<std::tm>(record.dateOnly));
//         v.set("date_time", static_cast<std::tm>(record.dateTime));

//         ind = i_ok;
//     }
// };

// template<> 
// struct type_conversion<Code::Databases::Record3>
// {
//     typedef values base_type;

//     static void from_base(values const& v, indicator /* ind */, Code::Databases::Record3& record)
//     {
//         record.phrase = v.get_indicator("phrase") == soci::i_ok 
//             ? v.get<std::string>("phrase") : std::optional<std::string>{};
            
//         record.number1 = v.get_indicator("number1") == soci::i_ok 
//             ? v.get<int>("number1") : std::optional<int>{};
            
//         record.number2 = v.get_indicator("number2") == soci::i_ok 
//             ? v.get<double>("number2") : std::optional<double>{};
//     }

//     static void to_base(const Code::Databases::Record3& record, values& v, indicator& ind)
//     {
//         v.set("phrase", record.phrase, 
//             record.phrase.has_value() ? soci::i_ok : soci::i_null);
            
//         v.set("number1", record.number1, 
//             record.number1.has_value() ? soci::i_ok : soci::i_null);

//         v.set("number2", record.number2, 
//             record.number2.has_value() ? soci::i_ok : soci::i_null);

//         // v.set("phrase", record.phrase);
//         // v.set("number1", record.number1);
//         // v.set("number2", record.number2);

//         ind = i_ok;
//     }
// };

// template<> 
// struct type_conversion<Code::Databases::Record4>
// {
//     typedef values base_type;

//     static void from_base(values const& v, indicator /* ind */, Code::Databases::Record4& record)
//     {
//         record.dateOnly = v.get_indicator("date_only") == soci::i_ok 
//             ? v.get<std::tm>("date_only") : std::optional<std::tm>{};

//         record.timeOnly = v.get_indicator("time_only") == soci::i_ok 
//             ? v.get<std::tm>("time_only") : std::optional<std::tm>{};

//         record.dateTime = v.get_indicator("date_time") == soci::i_ok 
//             ? v.get<std::tm>("date_time") : std::optional<std::tm>{};

//         // record.dateOnly = v.get<std::tm>("date_only");
//         // record.timeOnly = v.get<std::tm>("time_only");
//         // record.dateTime = v.get<std::tm>("date_time");
//     }

//     static void to_base(const Code::Databases::Record4& record, values& v, indicator& ind)
//     {
//         if (Code::Databases::GetIsPostgreSql())
//         {
//             std::stringstream ssTimeOnly;
//             ssTimeOnly << std::put_time(&record.timeOnly.value(), "%H:%M:%S");
//             v.set("time_only", ssTimeOnly.str(), record.timeOnly.has_value() ? soci::i_ok : soci::i_null);
//         }
//         else
//         {
//             v.set("time_only", static_cast<std::tm>(record.timeOnly.value()), 
//                 record.timeOnly.has_value() ? soci::i_ok : soci::i_null);
//         }

//         v.set("date_only", static_cast<std::tm>(record.dateOnly.value()), 
//             record.dateOnly.has_value() ? soci::i_ok : soci::i_null);

//         v.set("date_time", static_cast<std::tm>(record.dateTime.value()), 
//             record.dateTime.has_value() ? soci::i_ok : soci::i_null);

//         ind = i_ok;
//     }
// };

} // ~namespace soci
