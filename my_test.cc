#include <gtest/gtest.h>

TEST(MyVeryOwnTests, Test1) {
    EXPECT_EQ(1, 1) << "This should work.";
}