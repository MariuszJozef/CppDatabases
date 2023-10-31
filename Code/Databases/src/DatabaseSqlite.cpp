#include <iostream>
#include <filesystem>
// #include <optional>
#include <soci/sqlite3/soci-sqlite3.h>
#include "DatabaseSqlite.hpp"

namespace Code::Databases
{

void DatabaseSqlite::DropDatabase(const std::string& databaseName)
{
    if (!std::filesystem::exists(databaseName))
        return;
        
    std::error_code errorCode {};
    if (!std::filesystem::remove(databaseName, errorCode))
    {
        std::cerr << "Error: DatabaseSqlite::DropDatabase: " << errorCode.message() << "\n";
    }
    else
    {
        std::cout << "Database " << databaseName << " dropped\n";
    }
}

void DatabaseSqlite::CreateTableForRecord1(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         INTEGER PRIMARY KEY"
        << ", "
        << "true_or_false       BOOLEAN             NOT NULL"
        << ", "
        << "letter              CHARACTER(1)        NOT NULL"
        << ", "
        << "phrase              TEXT                NOT NULL"
        << ", "
        << "number1             INT                 NOT NULL"
        << ", "
        << "number2             REAL                NOT NULL"
        << ");";

    sql << composeQuery.str();

    std::cout << "Created table: " << tableName << "\n";
}

void DatabaseSqlite::CreateTableForRecord2(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         INTEGER PRIMARY KEY"
        << ", "
        << "date_only           DATE                NOT NULL"
        << ", "
        << "time_only           TIME                NOT NULL"
        << ", "
        << "date_time           DATETIME            NOT NULL"
        << ");";

    sql << composeQuery.str();

    std::cout << "Created table: " << tableName << "\n";
}

void DatabaseSqlite::CreateTableForRecord3(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         INTEGER PRIMARY KEY"
        << ", "
        << "phrase              TEXT"
        << ", "
        << "number1             INT"
        << ", "
        << "number2             REAL"
        << ");";

    sql << composeQuery.str();

    std::cout << "Created table: " << tableName << "\n";
}

void DatabaseSqlite::ExecuteQueries1()
{
    try {
        std::string databaseName {"SqliteDatabase1.db"};
        DropDatabase(databaseName);

        soci::session sql(soci::sqlite3, databaseName);
        std::cout << "Created and connected to database: " << databaseName << "\n";

        std::string tableName {"Table1"};
        DropTable(sql, tableName);
        CreateTableForRecord1(sql, tableName);
        TruncateTable(sql, tableName);

        CreateRecords1(sql, tableName, seedRecords1);
        CreateRecord1(sql, tableName, {false, 'f', "FFff", 6, 6.6});
        CreateRecord1(sql, tableName, {false, 'g', "GGgg", 7, 7.7});

        ReadRecords1(sql, tableName);
        ReadRecord1(sql, tableName, 2);

        CountRecords(sql, tableName);
        DeleteRecord(sql, tableName, 1);
        CountRecords(sql, tableName);

        UpdateRecord1(sql, tableName, 3, {false, 'C', "C__c", 303, 30.03});

        ReadRecords1(sql, tableName);
        ReadRow(sql, tableName, 2);
        ReadRow(sql, tableName, 2, {"true_or_false", "letter", "phrase"});
    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseSqlite::ExecuteQueries2()
{
    try {
        std::string databaseName {"SqliteDatabase1.db"};
        soci::session sql(soci::sqlite3, databaseName);
        std::cout << "Created and connected to database: " << databaseName << "\n";

        std::string tableName {"Table2"};
        DropTable(sql, tableName);
        CreateTableForRecord2(sql, tableName);
        TruncateTable(sql, tableName);

        CreateRecords2(sql, tableName, seedRecords2);
        CreateRecord2(sql, tableName, {
            {2006, 6, 16},
            {6, 36, 56, -1},
            {2006, 6, 16, 6, 36, 56}
        });
        
        CreateRecord2(sql, tableName, {
            {2007, 7, 17},
            {7, 37, 57, -1},
            {2007, 7, 17, 7, 37, 57}
        });

        ReadRecords2(sql, tableName);
        ReadRecord2(sql, tableName, 2);

        CountRecords(sql, tableName);
        DeleteRecord(sql, tableName, 2);
        CountRecords(sql, tableName);

        UpdateRecord2(sql, tableName, 4, {
            {1804, 4, 14},
            {18, 34, 54, -1},
            {1804, 4, 14, 18, 34, 54}
        });

        ReadRecords2(sql, tableName);
        ReadRow(sql, tableName, 3);
        ReadRow(sql, tableName, 3, {"date_only", "time_only", "date_time"});
    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseSqlite::ExecuteQueries3()
{
    try {
        std::string databaseName {"SqliteDatabase1.db"};
        soci::session sql(soci::sqlite3, databaseName);
        std::cout << "Created and connected to database: " << databaseName << "\n";

        std::string tableName {"Table3"};
        DropTable(sql, tableName);
        CreateTableForRecord3(sql, tableName);
        TruncateTable(sql, tableName);

        CreateRecords3(sql, tableName, seedRecords3);
        CreateRecord3(sql, tableName, {"Iii", 99, std::nullopt});
        CreateRecord3(sql, tableName, {"Jjj", std::nullopt, 10.10});
        CreateRecord3(sql, tableName, {std::nullopt, 11, 11.11});

        ReadRecords3(sql, tableName);
        ReadRecord3(sql, tableName, 2);

        CountRecords(sql, tableName);
        DeleteRecord(sql, tableName, 3);
        CountRecords(sql, tableName);

        UpdateRecord3(sql, tableName, 5, {"E_e", std::nullopt, 5.05});
        UpdateRecord3(sql, tableName, 6, {std::nullopt, 66, 6.06});
        UpdateRecord3(sql, tableName, 7, {std::nullopt, 77, std::nullopt});

        ReadRecords3(sql, tableName);
        ReadRow(sql, tableName, 7);
        ReadRow(sql, tableName, 6, {"number1", "number2"});
        ReadRow(sql, tableName, 2, {"number2"});
        ReadRow(sql, tableName, 5, {"number1"});
    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

} // ~namespace Code::Databases
