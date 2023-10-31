#pragma once 
#include "Database.hpp"

namespace Code::Databases
{

class DatabaseMsSqlServer final : public Database
{
public:
    void ExecuteQueries1() override;
    void ExecuteQueries2() override;
    void ExecuteQueries3() override;

private:
    // void CreateDatabase(soci::session& sql, const std::string& databaseName) override {}
    // void DropDatabase(soci::session& sql, const std::string& databaseName) override;

    // void CreateTableForRecord1(soci::session& sql, const std::string& tableName) override;
    // void CreateTableForRecord2(soci::session& sql, const std::string& tableName) override;
    // void CreateTableForRecord3(soci::session& sql, const std::string& tableName) override;
};

} // ~namespace Code::Databases
