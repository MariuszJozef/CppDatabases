#include <gmock/gmock.h>
#include "MockEntity.hpp"

namespace GTestGMock
{

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::Assign;
using ::testing::SetArgPointee;
// using ::testing::FieldsAre;

TEST(MockName, TestMockGui)
{
    // ARRANGE & SET EXPECTATIONS
    NiceMock<MockEntity> mockEntity;
    int number1 {0};
    int number2 {0};
    int number3 {0};
    int item1 {0};
    int item2 {0};
    int item3 {0};
    bool done1 {false};
    bool done2 {true};
    
    ON_CALL(mockEntity, DoAction1(1, 1.1, _))
        .WillByDefault(Return(true));

    EXPECT_CALL(mockEntity, DoAction2('a', _, _))
        .Times(3)
        .WillOnce(DoAll(Assign(&number1, 123), SetArgPointee<2>(111), Return(12.3)))
        .WillOnce(DoAll(Assign(&number2, -456), SetArgPointee<2>(222), Return(-45.6)))
        .WillOnce(DoAll(Assign(&number3, 789), SetArgPointee<2>(333), Return(78.9)));
    
    EXPECT_CALL(mockEntity, DoAction3())
        .Times(2)
        .WillOnce(Assign(&done1, true))
        .WillOnce(Assign(&done2, false));

    // ACT
    bool result1 = mockEntity.DoAction1(1, 1.1, "abcd");
    double result2 = mockEntity.DoAction2('a', number1, &item1);
    double result3 = mockEntity.DoAction2('a', number2, &item2);
    double result4 = mockEntity.DoAction2('a', number3, &item3);
    mockEntity.DoAction3();
    mockEntity.DoAction3();

    // ASSERT
    EXPECT_TRUE(result1) << "Failed: DoAction1(1, 1.1, 'abcd')";
    
    EXPECT_EQ(123, number1) << "Failed: DoAction2('a', &number1, item1)";
    EXPECT_EQ(111, item1) << "Failed: DoAction2('a', &number1, item1)";
    EXPECT_DOUBLE_EQ(12.3, result2) << "Failed: DoAction2('a', &number1)";

    EXPECT_EQ(-456, number2) << "Failed: DoAction2('a', &number2, item2)";
    EXPECT_EQ(222, item2) << "Failed: DoAction2('a', &number2, item2)";
    EXPECT_DOUBLE_EQ(-45.6, result3) << "Failed: DoAction2('a', &number2, item2)";

    EXPECT_EQ(789, number3) << "Failed: DoAction2('a', &number3, item3)";
    EXPECT_EQ(333, item3) << "Failed: DoAction2('a', &number3, item3)";
    EXPECT_DOUBLE_EQ(78.9, result4) << "Failed: DoAction2('a', &number3, item3)";

    EXPECT_TRUE(done1) << "Failed: DoAction3()";
    EXPECT_FALSE(done2) << "Failed: DoAction3()";
}

} // ~namespace GTestGMock
