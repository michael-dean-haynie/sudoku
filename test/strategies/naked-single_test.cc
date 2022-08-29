#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
    #include "naked-single.h"
    #include "cell.h"
    #include "test-helpers.h"
}

TEST(NakedSingleTests, ShouldReturnProgressEventPtrIfCellHasNakedSingle) {
    Grid grid;
    grid[0][0] = createCell(0, 0, 0);
    // set notes 2-9 to false, and leave 1 as true.
    for (int i = 2; i <= MAX_VAL; i++) {
        grid[0][0]->notes[i] = 0;
    }

    // prepare expected value
    ProgressEvent expected;
    expected.strategyName = strdup("nakedSingleStrat");
    expected.row = 0;
    expected.col = 0;
    expected.oldValue = 0;
    expected.newValue = 1;
    for (int i = 0; i <= MAX_VAL; i++) {
        // set 1 to true and the rest to false
        expected.oldNotes[i] = (i == 1) ? 1 : 0;
        expected.newNotes[i] = (i == 1) ? 1 : 0;
    }

    // get actual value and run assertions
    ProgressEvent *actual_p = nakedSingleStrat(&grid, 0, 0);
    ASSERT_TRUE(progressEventsAreEqual(&expected, actual_p));
}


TEST(NakedSingleTests, ShouldReturnNullIfCellValueIsNonZero) {
    Grid grid;
    grid[0][0] = createCell(0, 0, 1);

    ProgressEvent *expected = nullptr;
    ProgressEvent *actual = nakedSingleStrat(&grid, 0, 0);
    ASSERT_EQ(expected, actual);
}

TEST(NakedSingleTests, ShouldReturnNullIfCellHasMoreThan1Candidate) {
    Grid grid;
    grid[0][0] = createCell(0, 0, 0);
    // set notes 3-9 to false, and leave 1 and 2 as true.
    for (int i = 3; i <= MAX_VAL; i++) {
        grid[0][0]->notes[i] = 0;
    }

    ProgressEvent *expected = nullptr;
    ProgressEvent *actual = nakedSingleStrat(&grid, 0, 0);
    ASSERT_EQ(expected, actual);
}