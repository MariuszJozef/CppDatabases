#include <iostream>
#include <soci/postgresql/soci-postgresql.h>
#include "DatabasePostgreSql.hpp"

namespace Code::Databases
{

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
