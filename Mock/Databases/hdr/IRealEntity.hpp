#pragma once
#include <string>

namespace GTestGMock
{

class IRealEntity
{
public:
    virtual ~IRealEntity() = default;

    virtual bool DoAction1(int x, double y, const std::string& z) = 0;
    virtual double DoAction2(char letter, int number, int* pItem) = 0;
    virtual void DoAction3() const = 0;
};

} // ~namespace GTestGMock
