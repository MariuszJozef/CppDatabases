#include <iostream>
#include <iomanip>
#include "Database.hpp"
#include "ConvertRecordTypes.hpp"

namespace Code::Databases
{

bool Database::isPostgreSql {false};

bool GetIsPostgreSql()
{
    return Database::isPostgreSql;
}

void Database::CreateRecords1(soci::session& sql, const std::string& tableName, const std::vector<Record1>& records)
{
    std::stringstream composeQuery;
    composeQuery << "INSERT INTO"
        << " "
        << tableName
        << " "
        << "(true_or_false, letter, phrase, number1, number2)"
        << " VALUES "
        << "(:true_or_false, :letter, :phrase, :number1, :number2)"
        << ";";

    for (const auto& record : records)
    {
        sql << composeQuery.str(), soci::use(record);
    }
}

void Database::CreateRecord1(soci::session& sql, const std::string& tableName, const Record1&& record)
{
    std::stringstream composeQuery;
    composeQuery << "INSERT INTO"
        << " "
        << tableName
        << " "
        << "(true_or_false, letter, phrase, number1, number2)"
        << " VALUES "
        << "(:true_or_false, :letter, :phrase, :number1, :number2)"
        << ";";

    sql << composeQuery.str(), soci::use(record);
}

void Database::CreateRecords2(soci::session& sql, const std::string& tableName, const std::vector<Record2>& records)
{
    std::stringstream composeQuery;
    composeQuery << "INSERT INTO"
        << " "
        << tableName
        << " "
        << "(date_only, time_only, date_time)"
        << " VALUES "
        << "(:date_only, :time_only, :date_time)"
        << ";";

    for (const auto& record : records)
    {
        sql << composeQuery.str(), soci::use(record);
    }
}

void Database::CreateRecord2(soci::session& sql, const std::string& tableName, const Record2&& record)
{
    std::stringstream composeQuery;
    composeQuery << "INSERT INTO"
        << " "
        << tableName
        << " "
        << "(date_only, time_only, date_time)"
        << " VALUES "
        << "(:date_only, :time_only, :date_time)"
        << ";";

    sql << composeQuery.str(), soci::use(record);
}

void Database::CreateRecords3(soci::session& sql, const std::string& tableName, const std::vector<Record3>& records)
{
    std::stringstream composeQuery;
    composeQuery << "INSERT INTO"
        << " "
        << tableName
        << " "
        << "(phrase, number1, number2)"
        << " VALUES "
        << "(:phrase, :number1, :number2)"
        << ";";

    for (const auto& record : records)
    {
        sql << composeQuery.str(), soci::use(record);
    }
}

void Database::CreateRecord3(soci::session& sql, const std::string& tableName, const Record3&& record)
{
    std::stringstream composeQuery;
    composeQuery << "INSERT INTO"
        << " "
        << tableName
        << " "
        << "(phrase, number1, number2)"
        << " VALUES "
        << "(:phrase, :number1, :number2)"
        << ";";

    sql << composeQuery.str(), soci::use(record);
}

void Database::DeleteRecord(soci::session& sql, const std::string& tableName, int primaryKey)
{
    std::stringstream composeQuery;
    composeQuery << "DELETE FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    sql << composeQuery.str(), soci::use(primaryKey);

    std::cout << "Deleted record with primaryKey = " << primaryKey << "\n";
}

void Database::TruncateTable(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "DELETE FROM"
        << " "
        << tableName
        << ";";

    sql << composeQuery.str();

    std::cout << "Truncated table: " << tableName << "\n";
}

void Database::DropTable(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "DROP TABLE IF EXISTS"
        << " "
        << tableName
        << ";";

    sql << composeQuery.str();

    std::cout << "Dropped table: " << tableName << "\n";
}

void Database::DropDatabase(soci::session& sql, const std::string& databaseName)
{
    std::stringstream composeQuery;
    composeQuery << "DROP DATABASE IF EXISTS"
        << " "
        << databaseName
        << ";";

    sql << composeQuery.str();

    std::cout << "Dropped database: " << databaseName << "\n";
}

int DatabaseTestPrivate()
{
    std::cout << "Databases::DatabaseTestPrivate\n";
    return 11;
}

} // ~namespace Code::Databases
