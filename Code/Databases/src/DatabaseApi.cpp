#include "DatabaseApi.hpp"
#include "Database.hpp"
#include <iostream>
#include <iostream>
#include "DatabaseSqlite.hpp"
// #include "DatabaseMySql.hpp"
// #include "DatabasePostgreSql.hpp"
// #include "DatabaseMsSqlServer.hpp"

namespace Code::Databases
{

void QueryChosenDatabase(Backend backend)
{
    switch (backend)
    {
    case Backend::Sqlite:
    {
        std::cout << "QueryChosenDatabase --- Backend::Sqlite\n";
        // DatabaseSqlite databaseSqlite;
        // databaseSqlite.ExecuteQueries1();
        break;
    }
    case Backend::MySql:
    {
        std::cout << "QueryChosenDatabase --- Backend::MySql\n";
        // DatabaseMySql databaseMySql;
        // databaseMySql.ExecuteQueries1();
        break;
    }
    case Backend::PostgreSql:
    {
        std::cout << "QueryChosenDatabase --- Backend::PostgreSql\n";
        // DatabasePostgreSql databasePostgreSql;
        // databasePostgreSql.ExecuteQueries1();
        break;
    }
    case Backend::MsSqlServer:
    {
        std::cout << "QueryChosenDatabase --- Backend::MsSqlServer\n";
        // DatabaseMsSqlServer databaseMsSqlServer;
        // databaseMsSqlServer.ExecuteQueries1();
    }
    }
}

} // ~namespace Code::Databases


namespace Code::Databases
{

double DatabaseTestApi()
{
    std::cout << "Databases::DatabaseTestApi\n";
    return 0.1 + DatabaseTestPrivate();
}

} // ~namespace Code::Databases
