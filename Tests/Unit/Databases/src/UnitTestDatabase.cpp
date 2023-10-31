#include <gtest/gtest.h>
#include "Database.hpp"
#include "DatabaseApi.hpp"

namespace Tests::Unit::Database
{

TEST(UnitTestDatabase, CheckInt)
{
	// ARRANGE
    
    // ACT
    int result = Code::Databases::DatabaseTestPrivate();

    // ASSERT
    int expect {11};
    EXPECT_EQ(expect, result) << "Failed: DatabaseTestPrivate";
}

TEST(UnitTestDatabase, CheckDouble)
{
	// ARRANGE

    // ACT
    double result = Code::Databases::DatabaseTestApi();

    // ASSERT
    double expect {11.1};
    EXPECT_DOUBLE_EQ(expect, result) << "Failed: DatabaseTestApi";
}

} // ~namespace Tests::Unit::Database
