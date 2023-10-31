#pragma once 

namespace Code::Databases
{

enum class Backend
{
    Sqlite,
    MySql,
    PostgreSql,
    MsSqlServer
};

enum class Request
{
    CreateDatabase,
    UseDatabase,
    DropDatabase,
    CreateTable,
    TruncateTable,
    DropTable,
    CreateRecords,
    CreateRecord,
    CountRecords,
    ReadRecords,
    ReadRecord,
    UpdateRecord,
    DeleteRecord
};

} // ~namespace Code::Databases
