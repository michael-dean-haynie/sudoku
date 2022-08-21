#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
#include "test-helpers.h"
#include "hidden-single.h"
}

TEST(HiddenSingleTests, ShouldReturnProgressEventIfCellIsHasHiddenSingleForRow) {
    // arrange
    Grid *grid_p = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark other 8 cells in top row as NOT 5
    for (int col = 1; col < COLS; ++col) { // column index
        Cell *cell = (*grid_p)[0][col];
        cell->notes[5] = 0;
    }

    // create ProgressEvent with expected state
    ProgressEvent expected;
    expected.strategyName = strdup("hiddenSingleStrat");
    expected.row = 0;
    expected.col = 0;
    expected.oldValue = 0;
    expected.newValue = 5;
    expected.oldNotes[0] = 0;
    expected.newNotes[0] = 0;
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        expected.oldNotes[noteIdx] = 1; // used to be candidate for 1-9
        expected.newNotes[noteIdx] = 0;
    }
    expected.newNotes[5] = 1; // new value is 5 so only that note is true

   // act
    ProgressEvent *actual = hiddenSingleStrat(grid_p, 0, 0);

    // assert
    assertProgressEventsMatch(&expected, actual);
    ASSERT_EQ((*grid_p)[0][0]->value, 5) << "value should be assigned";
}

TEST(HiddenSingleTests, ShouldReturnProgressEventIfCellIsHasHiddenSingleForCollumn) {
    // arrange
    Grid *grid_p = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark other 8 cells in first column as NOT 5
    for (int row = 1; row < ROWS; ++row) { // row index
        Cell *cell = (*grid_p)[row][0];
        cell->notes[5] = 0;
    }

    // create ProgressEvent with expected state
    ProgressEvent expected;
    expected.strategyName = strdup("hiddenSingleStrat");
    expected.row = 0;
    expected.col = 0;
    expected.oldValue = 0;
    expected.newValue = 5;
    expected.oldNotes[0] = 0;
    expected.newNotes[0] = 0;
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        expected.oldNotes[noteIdx] = 1; // used to be candidate for 1-9
        expected.newNotes[noteIdx] = 0;
    }
    expected.newNotes[5] = 1; // new value is 5 so only that note is true

    // act
    ProgressEvent *actual = hiddenSingleStrat(grid_p, 0, 0);

    // assert
    assertProgressEventsMatch(&expected, actual);
    ASSERT_EQ((*grid_p)[0][0]->value, 5) << "value should be assigned";
}

TEST(HiddenSingleTests, ShouldReturnProgressEventIfCellIsHasHiddenSingleForBlock) {
    // arrange
    Grid *grid_p = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark other 8 cells in top left block as NOT 5
    for (int row = 0; row < 3; ++row) { // row index
        for (int col = 0; col < 3; ++col) {
            int isCellToSolve = (row == 0 && col == 0);
            if (!isCellToSolve) {
                Cell *cell = (*grid_p)[row][col];
                cell->notes[5] = 0;
            }
        }
    }

    // create ProgressEvent with expected state
    ProgressEvent expected;
    expected.strategyName = strdup("hiddenSingleStrat");
    expected.row = 0;
    expected.col = 0;
    expected.oldValue = 0;
    expected.newValue = 5;
    expected.oldNotes[0] = 0;
    expected.newNotes[0] = 0;
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        expected.oldNotes[noteIdx] = 1; // used to be candidate for 1-9
        expected.newNotes[noteIdx] = 0;
    }
    expected.newNotes[5] = 1; // new value is 5 so only that note is true

    // act
    ProgressEvent *actual = hiddenSingleStrat(grid_p, 0, 0);

    // assert
    assertProgressEventsMatch(&expected, actual);
    ASSERT_EQ((*grid_p)[0][0]->value, 5) << "value should be assigned";
}

TEST(HiddenSingleTests, ShouldReturnNullIfCellDoesNotHaveHiddenSingle) {
    // arrange
    Grid *grid_p = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark 7 other cells in top row as NOT 5
    for (int col = 2; col < COLS; ++col) { // column index
        Cell *cell = (*grid_p)[0][col];
        cell->notes[5] = 0;
    }

    // create ProgressEvent with expected state
    ProgressEvent *expected = nullptr;

    // act
    ProgressEvent *actual = hiddenSingleStrat(grid_p, 0, 0);

    // assert
    ASSERT_EQ(expected, actual);
    ASSERT_EQ((*grid_p)[0][0]->value, 0) << "value should not be assigned";
}
