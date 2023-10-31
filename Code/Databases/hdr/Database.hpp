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

    void CreateRecords1(soci::session& sql, const std::string& tableName, const std::vector<Record1>& records);
    void CreateRecords2(soci::session& sql, const std::string& tableName, const std::vector<Record2>& records);
    void CreateRecords3(soci::session& sql, const std::string& tableName, const std::vector<Record3>& records);
    
    void CreateRecord1(soci::session& sql, const std::string& tableName, const Record1&& record);
    void CreateRecord2(soci::session& sql, const std::string& tableName, const Record2&& record);
    void CreateRecord3(soci::session& sql, const std::string& tableName, const Record3&& record);

    int CountRecords(soci::session& sql, const std::string& tableName);

    std::vector<Record1> ReadRecords1(soci::session& sql, const std::string& tableName);
    std::vector<Record2> ReadRecords2(soci::session& sql, const std::string& tableName);
    std::vector<Record3> ReadRecords3(soci::session& sql, const std::string& tableName);
    
    Record1 ReadRecord1(soci::session& sql, const std::string& tableName, int primaryKey);
    Record2 ReadRecord2(soci::session& sql, const std::string& tableName, int primaryKey);
    Record3 ReadRecord3(soci::session& sql, const std::string& tableName, int primaryKey);

    soci::row ReadRow(soci::session& sql, const std::string& tableName, int primaryKey);
    soci::row ReadRow(soci::session& sql, const std::string& tableName, int primaryKey, const std::vector<std::string>& columnName);
    void PrintTableRow(const soci::row& tableRow);
    
    void UpdateRecord1(soci::session& sql, const std::string& tableName, int primaryKey, const Record1&& record);
    void UpdateRecord2(soci::session& sql, const std::string& tableName, int primaryKey, const Record2&& record);
    void UpdateRecord3(soci::session& sql, const std::string& tableName, int primaryKey, const Record3&& record);

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
