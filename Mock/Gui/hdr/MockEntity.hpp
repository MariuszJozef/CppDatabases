#pragma once
#include "IRealEntity.hpp"

namespace GTestGMock
{

class MockEntity : public IRealEntity
{
public:
    MOCK_METHOD(bool,   DoAction1, (int, double, const std::string&),   (override));
    MOCK_METHOD(double, DoAction2, (char, int, int*),                   (override));
    MOCK_METHOD(void,   DoAction3, (),                                  (const, override));
};

} // ~namespace GTestGMock
