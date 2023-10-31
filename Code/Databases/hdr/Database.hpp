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
    static bool isPostgreSql;

    friend bool GetIsPostgreSql();
};

bool GetIsPostgreSql();

int DatabaseTestPrivate();

} // ~namespace Code::Databases
