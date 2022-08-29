#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
#include "naked-single.h"
#include "cell.h"
#include "test-helpers.h"
}

TEST(nakedSingleStrategy, ShouldSetCellValueAndReturnProgressEvent_IfCellHasNakedSingle) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve

    // set notes 2-9 to false, and leave 1 as true.
    for (int i = 2; i <= MAX_VAL; i++) {
        (*grid)[0][0]->notes[i] = 0;
    }

    ProgressEventList expectedList;
    expectedList.length = 1;
    expectedList.items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->newValue = 1;
    expectedList.items[0]->strategyName = strdup("nakedSingleStrategy");
    // set notes[1] to true and the rest to false
    for (int i = 0; i <= MAX_VAL; i++) {
        expectedList.items[0]->oldNotes[i] = (i == 1) ? 1 : 0;
        expectedList.items[0]->newNotes[i] = (i == 1) ? 1 : 0;
    }

    // act
    ProgressEventList *actualList = nakedSingleStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(nakedSingleStrategy, ShouldJustReturnEmptyList_IfCellValueIsNonZero) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 1); // cell to solve

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = nakedSingleStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(nakedSingleStrategy, ShouldJustReturnEmptyList_IfCellHasMoreThan1Candidate) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve

    ProgressEventList expectedList;
    expectedList.length = 0;

    // act
    ProgressEventList *actualList = nakedSingleStrategy(grid, 0, 0);

    // assert
    assertProgressEventListsMatch(&expectedList, actualList);
}