#pragma once 
#include <soci/soci.h>
#include "TableRecords.hpp"

namespace Code::Databases
{

class Database
{
public:
    virtual ~Database() = default;

    virtual void ExecuteQueries1() = 0;
    virtual void ExecuteQueries2() = 0;
    virtual void ExecuteQueries3() = 0;

protected:
    virtual void CreateDatabase(soci::session& sql, const std::string& databaseName) = 0;

    virtual void CreateTableForRecord1(soci::session& sql, const std::string& tableName) = 0;
    virtual void CreateTableForRecord2(soci::session& sql, const std::string& tableName) = 0;
    virtual void CreateTableForRecord3(soci::session& sql, const std::string& tableName) = 0;


    void TruncateTable(soci::session& sql, const std::string& tableName);
    void DropTable(soci::session& sql, const std::string& tableName);
    void DeleteRecord(soci::session& sql, const std::string& tableName, int primaryKey);
    virtual void DropDatabase(soci::session& sql, const std::string& databaseName);

protected:
    static bool isPostgreSql;

    friend bool GetIsPostgreSql();
};

bool GetIsPostgreSql();

int DatabaseTestPrivate();

} // ~namespace Code::Databases
