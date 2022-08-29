#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
#include "test-helpers.h"
#include "hidden-single.h"
}

TEST(hiddenSingleStrategy, ShouldSetCellValueAndReturnProgressEvent_IfCellIsHasHiddenSingleForRow) {
    // arrange
    Grid *grid = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark other 8 cells in top row as NOT 5
    for (int col = 1; col < COLS; ++col) { // column index
        Cell *cell = (*grid)[0][col];
        cell->notes[5] = 0;
    }

    ProgressEventList expectedList;
    expectedList.length = 1;
    expectedList.items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->newValue = 5;
    expectedList.items[0]->strategyName = strdup("hiddenSingleStrategy");
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        expectedList.items[0]->oldNotes[noteIdx] = 1; // used to be a candidate for values 1-9
        expectedList.items[0]->newNotes[noteIdx] = 0;
    }
    expectedList.items[0]->newNotes[5] = 1; // new value is 5 so only that note is true

   // act
    ProgressEventList *actualList = hiddenSingleStrategy(grid, 0, 0);

    // assert
    ASSERT_EQ((*grid)[0][0]->value, 5) << "value should be assigned";
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(hiddenSingleStrategy, ShouldSetCellValueAndReturnProgressEvent_IfCellIsHasHiddenSingleForColumn) {
    // arrange
    Grid *grid = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark other 8 cells in first column as NOT 5
    for (int row = 1; row < ROWS; ++row) { // row index
        Cell *cell = (*grid)[row][0];
        cell->notes[5] = 0;
    }

    ProgressEventList expectedList;
    expectedList.length = 1;
    expectedList.items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->newValue = 5;
    expectedList.items[0]->strategyName = strdup("hiddenSingleStrategy");
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        expectedList.items[0]->oldNotes[noteIdx] = 1; // used to be a candidate for values 1-9
        expectedList.items[0]->newNotes[noteIdx] = 0;
    }
    expectedList.items[0]->newNotes[5] = 1; // new value is 5 so only that note is true

    // act
    ProgressEventList *actualList = hiddenSingleStrategy(grid, 0, 0);

    // assert
    ASSERT_EQ((*grid)[0][0]->value, 5) << "value should be assigned";
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(hiddenSingleStrategy, ShouldSetCellValueAndReturnProgressEvent_IfCellIsHasHiddenSingleForBlock) {
    // arrange
    Grid *grid = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark other 8 cells in top left block as NOT 5
    for (int row = 0; row < 3; ++row) { // row index
        for (int col = 0; col < 3; ++col) {
            int isCellToSolve = (row == 0 && col == 0);
            if (!isCellToSolve) {
                Cell *cell = (*grid)[row][col];
                cell->notes[5] = 0;
            }
        }
    }

    ProgressEventList expectedList;
    expectedList.length = 1;
    expectedList.items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->newValue = 5;
    expectedList.items[0]->strategyName = strdup("hiddenSingleStrategy");
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        expectedList.items[0]->oldNotes[noteIdx] = 1; // used to be a candidate for values 1-9
        expectedList.items[0]->newNotes[noteIdx] = 0;
    }
    expectedList.items[0]->newNotes[5] = 1; // new value is 5 so only that note is true

    // act
    ProgressEventList *actualList = hiddenSingleStrategy(grid, 0, 0);

    // assert
    ASSERT_EQ((*grid)[0][0]->value, 5) << "value should be assigned";
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(hiddenSingleStrategy, ShouldJustReturnEmptyList_IfCellDoesNotHaveHiddenSingle) {
    // arrange
    Grid *grid = createEmptyGrid();

    // the cell-to-solve is (0, 0)
    // mark 7 other cells in top row as NOT 5 (so there are still 2 that could be 5)
    for (int col = 2; col < COLS; ++col) { // column index
        Cell *cell = (*grid)[0][col];
        cell->notes[5] = 0;
    }

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = hiddenSingleStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(hiddenSingleStrategy, ShouldJustReturnEmptyList_IfCellValueIsNonZero) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 1); // cell to solve

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = hiddenSingleStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}
