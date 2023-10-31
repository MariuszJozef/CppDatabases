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


int DatabaseTestPrivate()
{
    std::cout << "Databases::DatabaseTestPrivate\n";
    return 11;
}

} // ~namespace Code::Databases
