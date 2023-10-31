#include <iostream>
#include <soci/postgresql/soci-postgresql.h>
#include "DatabasePostgreSql.hpp"

namespace Code::Databases
{

DatabasePostgreSql::DatabasePostgreSql()
{
    Database::isPostgreSql = true;
}

void DatabasePostgreSql::CreateDatabase(soci::session& sql, const std::string& databaseName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE DATABASE"
        << " "
        << databaseName
        << ";";

    sql << composeQuery.str();

    std::cout << "Created database: " << databaseName << "\n";
}

void DatabasePostgreSql::CreateTableForRecord1(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         SERIAL PRIMARY KEY"
        << ", "
        << "true_or_false       BOOLEAN"
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

void DatabasePostgreSql::CreateTableForRecord2(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         SERIAL PRIMARY KEY"
        << ", "
        << "date_only           DATE                NOT NULL"
        << ", "
        << "time_only           TIME                NOT NULL"
        << ", "
        << "date_time           TIMESTAMP           NOT NULL"
        << ");";

    sql << composeQuery.str();

    std::cout << "created table: " << tableName << "\n";
}

void DatabasePostgreSql::CreateTableForRecord3(soci::session& sql, const std::string& tableName)
{
    std::stringstream composeQuery;
    composeQuery << "CREATE TABLE IF NOT EXISTS"
        << " "
        << tableName
        << " ("
        << "primary_key         SERIAL PRIMARY KEY"
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

void DatabasePostgreSql::ExecuteQueries1()
{
// CAVEAT: Postgres converts to and expects lowercase; better to use snake_case here!
    // std::string databaseNameLowerCase {"postgresql_database1"};
    std::string databaseNameLowerCase {"cpp_database1"};
    std::string tableNameLowerCase {"table1"};
    
    try {
        std::string connectionStr {"dbname="};
        connectionStr += databaseNameLowerCase;

        {
/*
            1st connect to the default "postgres" database
            2nd create another (user requested) database for a given task
            3rd connect to that specific database - otherwise could fail to connect 
                if the user requested database didn't yet exist
*/
            soci::session sql(soci::postgresql, "dbname=postgres");
            std::cout << "Connected to database: postgres\n";
            DropDatabase(sql, databaseNameLowerCase);
            CreateDatabase(sql, databaseNameLowerCase);
        }

        soci::session sql(soci::postgresql, connectionStr);
        std::cout << "Connected to database: " << databaseNameLowerCase << "\n";

        DropTable(sql, tableNameLowerCase);
        CreateTableForRecord1(sql, tableNameLowerCase);
        TruncateTable(sql, tableNameLowerCase);

        CreateRecords1(sql, tableNameLowerCase, seedRecords1);
        CreateRecord1(sql, tableNameLowerCase, {false, 'f', "FFff", 6, 6.6});
        CreateRecord1(sql, tableNameLowerCase, {false, 'g', "GGgg", 7, 7.7});

        ReadRecords1(sql, tableNameLowerCase);
        ReadRecord1(sql, tableNameLowerCase, 2);

        CountRecords(sql, tableNameLowerCase);
        DeleteRecord(sql, tableNameLowerCase, 1);
        CountRecords(sql, tableNameLowerCase);
        
        UpdateRecord1(sql, tableNameLowerCase, 3, {false, 'C', "C__c", 303, 30.03});

        ReadRecords1(sql, tableNameLowerCase);
        // ReadRow(sql, tableNameLowerCase, 2);
        // ReadRow(sql, tableNameLowerCase, 2, {"true_or_false", "letter", "phrase"});
    }
    catch (const soci::postgresql_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabasePostgreSql::ExecuteQueries2()
{
    try {
        // CAVEAT: Postgres converts to and expects lowercase!
        // std::string databaseNameLowerCase {"postgresql_database1"};
        std::string databaseNameLowerCase {"cpp_database1"};
        std::string connectionStr {"dbname="};
        connectionStr += databaseNameLowerCase;
/*
        This database should already exist so can connect to it directly 
        without goint through the default database "postgres"
*/
        soci::session sql(soci::postgresql, connectionStr);
        std::cout << "Connected to database: " << databaseNameLowerCase << "\n";

        std::string tableNameLowerCase {"table2"};
        DropTable(sql, tableNameLowerCase);
        CreateTableForRecord2(sql, tableNameLowerCase);
        TruncateTable(sql, tableNameLowerCase);

        CreateRecords2(sql, tableNameLowerCase, seedRecords2);
        CreateRecord2(sql, tableNameLowerCase, {
            {2006, 6, 16},
            {6, 36, 56, -1},
            {2006, 6, 16, 6, 36, 56}
        });
        
        CreateRecord2(sql, tableNameLowerCase, {
            {2007, 7, 17},
            {7, 37, 57, -1},
            {2007, 7, 17, 7, 37, 57}
        });

        ReadRecords2(sql, tableNameLowerCase);
        ReadRecord2(sql, tableNameLowerCase, 2);

        CountRecords(sql, tableNameLowerCase);
        DeleteRecord(sql, tableNameLowerCase, 2);
        CountRecords(sql, tableNameLowerCase);

        UpdateRecord2(sql, tableNameLowerCase, 4, {
            {1804, 4, 14},
            {18, 34, 54, -1},
            {1804, 4, 14, 18, 34, 54}
        });

        ReadRecords2(sql, tableNameLowerCase);
        // ReadRow(sql, tableNameLowerCase, 3);
        // ReadRow(sql, tableNameLowerCase, 3, {"date_only", "time_only", "date_time"});

    }
    catch (const soci::postgresql_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabasePostgreSql::ExecuteQueries3()
{
    try {
        // CAVEAT: Postgres converts to and expects lowercase!
        // std::string databaseNameLowerCase {"postgresql_database1"};
        std::string databaseNameLowerCase {"cpp_database1"};
        std::string connectionStr {"dbname="};
        connectionStr += databaseNameLowerCase;
/*
        This database should already exist so can connect to it directly 
        without goint through the default database "postgres"
*/
        soci::session sql(soci::postgresql, connectionStr);
        std::cout << "Connected to database: " << databaseNameLowerCase << "\n";

        std::string tableNameLowerCase {"table3"};
        DropTable(sql, tableNameLowerCase);
        CreateTableForRecord3(sql, tableNameLowerCase);
        TruncateTable(sql, tableNameLowerCase);

        CreateRecords3(sql, tableNameLowerCase, seedRecords3);
        CreateRecord3(sql, tableNameLowerCase, {"Iii", 99, std::nullopt});
        CreateRecord3(sql, tableNameLowerCase, {"Jjj", std::nullopt, 10.10});
        CreateRecord3(sql, tableNameLowerCase, {std::nullopt, 11, 11.11});

        ReadRecords3(sql, tableNameLowerCase);
        ReadRecord3(sql, tableNameLowerCase, 2);

        CountRecords(sql, tableNameLowerCase);
        DeleteRecord(sql, tableNameLowerCase, 3);
        CountRecords(sql, tableNameLowerCase);

        UpdateRecord3(sql, tableNameLowerCase, 5, {"E_e", std::nullopt, 5.05});
        UpdateRecord3(sql, tableNameLowerCase, 6, {std::nullopt, 66, 6.06});
        UpdateRecord3(sql, tableNameLowerCase, 7, {std::nullopt, 77, std::nullopt});

        ReadRecords3(sql, tableNameLowerCase);
        // ReadRow(sql, tableNameLowerCase, 7);
        // ReadRow(sql, tableNameLowerCase, 6, {"number1", "number2"});
        // ReadRow(sql, tableNameLowerCase, 2, {"number2"});
        // ReadRow(sql, tableNameLowerCase, 5, {"number1"});
    }
    catch (const soci::postgresql_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

} // ~namespace Code::Databases
