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

int Database::CountRecords(soci::session& sql, const std::string& tableName)
{
    int count {0};
    std::stringstream composeQuery;
    composeQuery << "SELECT COUNT(*) FROM"
        << " "
        << tableName
        << ";";

    sql << composeQuery.str(), soci::into(count);

    std::cout << "Table '" << tableName << "' has " << count << " row(s)\n";

    return count;
}

std::vector<Record1> Database::ReadRecords1(soci::session& sql, const std::string& tableName)
{
    Record1 record {};
    std::vector<Record1> records;
    soci::indicator ind;
    std::stringstream composeQuery;
    composeQuery << "SELECT * FROM"
        << " "
        << tableName
        << ";";

    soci::statement st = (
        sql.prepare << composeQuery.str(), soci::into(record, ind)
    );

    st.execute();

    while (st.fetch())
    {
        records.push_back(record);
        std::cout << record << "\n";
    }

    return records;
}

Record1 Database::ReadRecord1(soci::session& sql, const std::string& tableName, int primaryKey)
{
    Record1 record {};
    soci::indicator ind;
    std::stringstream composeQuery;
    composeQuery << "SELECT * FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    sql << composeQuery.str(), soci::use(primaryKey), soci::into(record, ind);

    std::cout << primaryKey << ": " << record << "\n";

    return record;
}

std::vector<Record2> Database::ReadRecords2(soci::session& sql, const std::string& tableName)
{
    Record2 record {};
    std::vector<Record2> records;
    soci::indicator ind;
    std::stringstream composeQuery;
    composeQuery << "SELECT * FROM"
        << " "
        << tableName
        << ";";

    soci::statement st = (
        sql.prepare << composeQuery.str(), soci::into(record, ind)
    );

    st.execute();

    while (st.fetch())
    {
        records.push_back(record);
        std::cout << record << "\n";
    }

    return records;
}

Record2 Database::ReadRecord2(soci::session& sql, const std::string& tableName, int primaryKey)
{
    Record2 record {};
    soci::indicator ind;
    std::stringstream composeQuery;
    composeQuery << "SELECT * FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    sql << composeQuery.str(), soci::use(primaryKey), soci::into(record, ind);

    std::cout << primaryKey << ": " << record << "\n";

    return record;
}

std::vector<Record3> Database::ReadRecords3(soci::session& sql, const std::string& tableName)
{
    Record3 record {};
    std::vector<Record3> records;
    soci::indicator ind;
    std::stringstream composeQuery;
    composeQuery << "SELECT * FROM"
        << " "
        << tableName
        << ";";

    soci::statement st = (
        sql.prepare << composeQuery.str(), soci::into(record, ind)
    );

    st.execute();

    while (st.fetch())
    {
        records.push_back(record);
        std::cout << record << "\n";
    }

    return records;
}

Record3 Database::ReadRecord3(soci::session& sql, const std::string& tableName, int primaryKey)
{
    Record3 record {};
    soci::indicator ind;
    std::stringstream composeQuery;
    composeQuery << "SELECT * FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    sql << composeQuery.str(), soci::use(primaryKey), soci::into(record, ind);

    std::cout << primaryKey << ": " << record << "\n";

    return record;
}

void Database::UpdateRecord1(soci::session& sql, const std::string& tableName, int primaryKey, const Record1&& record)
{
    // First check that a record with such primary key exists
    std::stringstream composeQuery;
    composeQuery << "SELECT primary_key FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    int foundKey;
    soci::indicator ind;

    sql << composeQuery.str(), soci::use(primaryKey), soci::into(foundKey, ind);

    if (sql.got_data())
    {
        // Now update it
        std::stringstream composeQuery;
        composeQuery << "UPDATE"
            << " "
            << tableName
            << " "
            << "SET true_or_false = :true_or_false, letter = :letter, phrase = :phrase, number1 = :number1, number2 = :number2"
            << " "
            << "WHERE primary_key = :primary_key;";

        sql << composeQuery.str()
            , soci::use(static_cast<int>(record.trueOrFalse))
            , soci::use(record.letter)
            , soci::use(record.phrase)
            , soci::use(record.number1)
            , soci::use(record.number2)
            , soci::use(primaryKey);

        std::cout << "Updated record with primaryKey = " << primaryKey << ": "
            << record << "\n";
    }
    else
    {
        std::cout << "No record with primaryKey = " << primaryKey << ", cannot update!\n";
    }
}

void Database::UpdateRecord2(soci::session& sql, const std::string& tableName, int primaryKey, const Record2&& record)
{
    // First check that a record with such primary key exists
    std::stringstream composeQuery;
    composeQuery << "SELECT primary_key FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    int foundKey;
    soci::indicator ind;

    sql << composeQuery.str(), soci::use(primaryKey), soci::into(foundKey, ind);

    if (sql.got_data())
    {
        // Now update it
        std::stringstream composeQuery;
        composeQuery << "UPDATE"
            << " "
            << tableName
            << " "
            << "SET date_only = :date_only, time_only = :time_only, date_time = :date_time"
            << " "
            << "WHERE primary_key = :primary_key;";

        if (isPostgreSql)
        {
            std::stringstream ssTimeOnly;
            ssTimeOnly << std::put_time(&record.timeOnly, "%H:%M:%S");

            sql << composeQuery.str()
            , soci::use(static_cast<std::tm>(record.dateOnly))
            , soci::use(ssTimeOnly.str())
            , soci::use(static_cast<std::tm>(record.dateTime))
            , soci::use(primaryKey);

        }
        else
        {
            sql << composeQuery.str()
                , soci::use(static_cast<std::tm>(record.dateOnly))
                , soci::use(static_cast<std::tm>(record.timeOnly))
                , soci::use(static_cast<std::tm>(record.dateTime))
                , soci::use(primaryKey);
        }

        std::cout << "Updated record with primaryKey = " << primaryKey << ": "
            << record << "\n";
    }
    else
    {
        std::cout << "No record with primaryKey = " << primaryKey << ", cannot update!\n";
    }
}

void Database::UpdateRecord3(soci::session& sql, const std::string& tableName, int primaryKey, const Record3&& record)
{
    // First check that a record with such primary key exists
    std::stringstream composeQuery;
    composeQuery << "SELECT primary_key FROM"
        << " "
        << tableName
        << " "
        << "WHERE primary_key = :primary_key"
        << ";";

    int foundKey;
    soci::indicator ind;

    sql << composeQuery.str(), soci::use(primaryKey), soci::into(foundKey, ind);

    if (sql.got_data())
    {
        // Now update it
        std::stringstream composeQuery;
        composeQuery << "UPDATE"
            << " "
            << tableName
            << " "
            << "SET phrase = :phrase, number1 = :number1, number2 = :number2"
            << " "
            << "WHERE primary_key = :primary_key;";

        sql << composeQuery.str()
            , soci::use(record.phrase)
            , soci::use(record.number1)
            , soci::use(record.number2)
            , soci::use(primaryKey);

        std::cout << "Updated record with primaryKey = " << primaryKey << ": "
            << record << "\n";
    }
    else
    {
        std::cout << "No record with primaryKey = " << primaryKey << ", cannot update!\n";
    }
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
