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
