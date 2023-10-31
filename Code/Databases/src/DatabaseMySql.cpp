#include <iostream>
#include <soci/mysql/soci-mysql.h>
#include "DatabaseMySql.hpp"

namespace Code::Databases
{

void DatabaseMySql::CreateDatabase(soci::session& sql, const std::string& databaseName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE DATABASE IF NOT EXISTS"
        << " "
        << databaseName
        << ";";

    sql << composeQuery.str();

    std::cout << "Created database: " << databaseName << "\n";
}

void DatabaseMySql::UseDatabase(soci::session& sql, const std::string& databaseName)
{
    std::stringstream composeQuery;
    composeQuery << "USE"
        << " "
        << databaseName
        << ";";

    sql << composeQuery.str();

    std::cout << "Connected to database: " << databaseName << "\n";
}

void DatabaseMySql::CreateTableForRecord1(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         INT AUTO_INCREMENT PRIMARY KEY"
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

    std::cout << "created table: " << tableName << "\n";
}

void DatabaseMySql::CreateTableForRecord2(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         INT AUTO_INCREMENT PRIMARY KEY"
        << ", "
        << "date_only           DATE                NOT NULL"
        << ", "
        << "time_only           TIME                NOT NULL"
        << ", "
        << "date_time           DATETIME            NOT NULL"
        << ");";

    sql << composeQuery.str();

    std::cout << "created table: " << tableName << "\n";
}

void DatabaseMySql::CreateTableForRecord3(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         INT AUTO_INCREMENT PRIMARY KEY"
        << ", "
        << "phrase              TEXT"
        << ", "
        << "number1             INT"
        << ", "
        << "number2             REAL"
        << ");";

    sql << composeQuery.str();

    std::cout << "created table: " << tableName << "\n";
}

void DatabaseMySql::ExecuteQueries1()
{
    try {
        soci::session sql(soci::mysql, "db=mysql user=root");
        std::cout << "Connected to mysql (no database selected)\n";

        std::string databaseName {"MySqlDatabase1"};
        DropDatabase(sql, databaseName);
        CreateDatabase(sql, databaseName);
        UseDatabase(sql, databaseName);

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
    }
    catch (const soci::mysql_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseMySql::ExecuteQueries2()
{
    try {
        soci::session sql(soci::mysql, "db=mysql user=root");
        std::cout << "Connected to mysql (no database selected)\n";

        std::string databaseName {"MySqlDatabase1"};
        CreateDatabase(sql, databaseName);
        UseDatabase(sql, databaseName);

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

    }
    catch (const soci::mysql_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseMySql::ExecuteQueries3()
{
    try {
        soci::session sql(soci::mysql, "db=mysql user=root");
        std::cout << "Connected to mysql (no database selected)\n";

        std::string databaseName {"MySqlDatabase1"};
        CreateDatabase(sql, databaseName);
        UseDatabase(sql, databaseName);

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
    }
    catch (const soci::mysql_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

} // ~namespace Code::Databases
