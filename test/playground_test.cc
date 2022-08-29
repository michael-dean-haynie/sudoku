#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
#include "test-helpers.h"
}

TEST(Playground, Test1) {
    ASSERT_EQ(1, 1);
}