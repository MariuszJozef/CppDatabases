#include <iostream>
#include <soci/postgresql/soci-postgresql.h>
#include "DatabasePostgreSql.hpp"

namespace Code::Databases
{

void DatabasePostgreSql::ExecuteQueries1()
{
    try {

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
