#include <gtest/gtest.h>

extern "C" {
    #include "no-duplicates.h"
    #include "test-helpers.h"
}

TEST(NoDuplictesTests, ShouldReturnProgressEventIfRowHasValue) {
    // arrange
    Grid grid;
    for(int col = 0; col < COLS; col++) {
        grid[0][col] = createCell(0, col, 0); // fill row with defaults
    }
    grid[0][0] = createCell(0, 0, 0); // cell to solve
    grid[0][8] = createCell(0, 8, 5); // cell with value

    ProgressEvent expected;
    expected.strat_p = strdup("noDuplicatesStrat");
    expected.row = 0;
    expected.col = 0;
    expected.oldValue = 0;
    expected.newValue = 0;
    for(int i = 0; i <= MAX_VAL; i++) {
        if (i == 0) { // notes at [0] is always 0
            expected.oldNotes[i] = 0;
            expected.newNotes[i] = 0;
        } else {
            expected.oldNotes[i] = 1;
            expected.newNotes[i] = 1;
        }
    }
    expected.newNotes[5] = 0;

    // act
    ProgressEvent *actual = noDuplicatesStrat(&grid, 0, 0);
    printProgressEvent(&expected);
    printProgressEvent(actual);

    // assert
    ASSERT_TRUE(progressEventsAreEqual(&expected, actual));

}

TEST(NoDuplictesTests, ShouldReturnProgressEventIfColHasValue) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve
    (*grid)[8][0] = createCell(8, 0, 5); // cell with value

    ProgressEvent expected;
    expected.strat_p = strdup("noDuplicatesStrat");
    expected.row = 0;
    expected.col = 0;
    expected.oldValue = 0;
    expected.newValue = 0;
    for(int i = 0; i <= MAX_VAL; i++) {
        if (i == 0) { // notes at [0] is always 0
            expected.oldNotes[i] = 0;
            expected.newNotes[i] = 0;
        } else {
            expected.oldNotes[i] = 1;
            expected.newNotes[i] = 1;
        }
    }
    expected.newNotes[5] = 0;

    // act
    ProgressEvent *actual = noDuplicatesStrat(grid, 0, 0);
    printProgressEvent(&expected);
    printProgressEvent(actual);

    // assert
    ASSERT_TRUE(progressEventsAreEqual(&expected, actual));

}

