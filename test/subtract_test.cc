#include <gtest/gtest.h>
extern "C" {
    #include "subtract.h"
}

TEST(SubtractTests, Subtract2From4) {
    int actualResult = subtract(4, 2);
    int expectedResult = 2;
    EXPECT_EQ(actualResult, expectedResult) << "subtract(4, 2) should be 2.";
}