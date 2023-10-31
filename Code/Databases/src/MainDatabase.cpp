#include "DatabaseApi.hpp"

int main()
{
    Code::Databases::QueryChosenDatabase(Code::Databases::Backend::Sqlite);
    Code::Databases::QueryChosenDatabase(Code::Databases::Backend::MySql);
    Code::Databases::QueryChosenDatabase(Code::Databases::Backend::PostgreSql);
    Code::Databases::QueryChosenDatabase(Code::Databases::Backend::MsSqlServer);

    Code::Databases::DatabaseTestApi();
}
