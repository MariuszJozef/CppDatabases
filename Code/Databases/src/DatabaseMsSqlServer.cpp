#include <iostream>
#include <soci/odbc/soci-odbc.h>
#include "DatabaseMsSqlServer.hpp"

namespace Code::Databases
{

void DatabaseMsSqlServer::ExecuteQueries1()
{
    try {
        // soci::session sql(soci::odbc, "filedsn=c:\\my.dsn");
        // TODO
    }
    catch (const soci::odbc_soci_error& e)
    {
        std::cerr << "Catch Odbc: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseMsSqlServer::ExecuteQueries2()
{
    try {
        // soci::session sql(soci::odbc, "filedsn=c:\\my.dsn");
    
    }
    catch (const soci::odbc_soci_error& e)
    {
        std::cerr << "Catch Odbc: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

void DatabaseMsSqlServer::ExecuteQueries3()
{
    try {
        // soci::session sql(soci::odbc, "filedsn=c:\\my.dsn");
    
    }
    catch (const soci::odbc_soci_error& e)
    {
        std::cerr << "Catch Odbc: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
    catch (const soci::soci_error& e)
    {
        std::cerr << "Catch: " << e.what() << " --- " << e.get_error_category() << '\n';
    }
}

} // ~namespace Code::Databases
