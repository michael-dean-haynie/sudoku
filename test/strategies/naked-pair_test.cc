#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
#include "naked-pair.h"
#include "test-helpers.h"
}

TEST(nakedPairStrategy, ShoudJustReturnEmptyList_IfCellValueIsNonZero) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 5); // cell to solve

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = nakedPairStrategy(grid, 0 , 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(nakedPairStrategy, ShoudJustReturnEmptyList_IfCellDoesNotHaveExactlyTwoNotes) {
    // arrange
    Grid *grid = createEmptyGrid(); // cell to solve (0, 0) by default has 9 notes

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = nakedPairStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(nakedPairStrategy, ShoudJustReturnEmptyList_IfCellHasExactlyTwoNotesButHasNoOtherCellsDo) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0);
    // leave 1 and 2, remove all other candidates
    for (int noteIdx = 3; noteIdx <= MAX_VAL; ++noteIdx) {
        (*grid)[0][0]->notes[noteIdx] = 0;
    }

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = nakedPairStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(nakedPairStrategy, ShoudUpdateNotesAndReturnProgressEvents_IfTwoCellsHaveTheSameTwoNotesInRow) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0); // first cell in pair
    (*grid)[0][3] = createCell(0, 3, 0); // second cell in pair
    // leave 1 and 2, remove all other candidates
    for (int noteIdx = 3; noteIdx <= MAX_VAL; ++noteIdx) {
        (*grid)[0][0]->notes[noteIdx] = 0;
        (*grid)[0][3]->notes[noteIdx] = 0;
    }

    ProgressEventList expectedList;
    expectedList.length = 2;
    expectedList.items = (ProgressEvent**) malloc(2 * sizeof(ProgressEvent*));

    // cell (0, 1) will have a value set, so it should not get updated
    (*grid)[0][1] = createCell(0, 1, 3);

    // cell (0, 2) will have a value set, so it should not get updated
    (*grid)[0][2] = createCell(0, 2, 4);

    // cell (0, 4) will have 9 notes, so it should get updated
    (*grid)[0][4] = createCell(0, 4, 0);
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->strategyName = strdup("nakedPairStrategy");
    expectedList.items[0]->col = 4;
    expectedList.items[0]->newNotes[1] = 0;
    expectedList.items[0]->newNotes[2] = 0;

    // cell (0, 5) will have 8 notes (0 for one of the pair values), so it should get updated
    (*grid)[0][5] = createCell(0, 5, 0);
    (*grid)[0][5]->notes[1] = 0;
    expectedList.items[1] = createTemplateProgressEvent();
    expectedList.items[1]->strategyName = strdup("nakedPairStrategy");
    expectedList.items[1]->col = 5;
    expectedList.items[1]->oldNotes[1] = 0;
    expectedList.items[1]->newNotes[1] = 0;
    expectedList.items[1]->newNotes[2] = 0;

    // cell (0, 6) will have 7 notes (0 for both of the pair values), so it should not get updated
    (*grid)[0][6] = createCell(0, 6, 0);
    (*grid)[0][6]->notes[1] = 0;
    (*grid)[0][6]->notes[2] = 0;

    // cells (0, 7) and (0, 9) will have values set, so they should not get updated
    (*grid)[0][7] = createCell(0, 7, 8);
    (*grid)[0][8] = createCell(0, 8, 9);

    // act
    ProgressEventList *actualList = nakedPairStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}
