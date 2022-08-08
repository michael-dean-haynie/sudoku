#include <gtest/gtest.h>

extern "C" {
    #include "naked-single.h"
    #include "cell.h"
}

TEST(NakedSingleTests, ShouldReturnNullWhenCellValueIsNonZero) {
    Grid grid;
    grid[0][0] = createCell(0, 0, 1);

    ProgressEvent *expected = nullptr;
    ProgressEvent *actual = nakedSingleStrat(&grid, 0, 0);
    EXPECT_EQ(expected, actual);
}