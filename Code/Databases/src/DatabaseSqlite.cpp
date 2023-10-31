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
