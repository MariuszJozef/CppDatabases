#include <iostream>
// #include <optional>
#include <soci/sqlite3/soci-sqlite3.h>
#include "DatabaseSqlite.hpp"

namespace Code::Databases
{

void DatabaseSqlite::ExecuteQueries1()
{
    try {

    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseSqlite::ExecuteQueries2()
{
    try {

    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseSqlite::ExecuteQueries3()
{
    try {

    }
    catch (const soci::sqlite3_soci_error& e)
    {
        std::cerr << "Catch " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

} // ~namespace Code::Databases
