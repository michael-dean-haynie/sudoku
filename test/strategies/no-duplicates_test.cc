#include <gtest/gtest.h>
#include "assertion-helpers.h"

extern "C" {
#include "no-duplicates.h"
#include "cell.h"
#include "test-helpers.h"
}

TEST(noDuplicatesStrategy, ShouldRemoveCandidateAndReturnProgressEvent_IfRowHasValue) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve
    (*grid)[0][8] = createCell(0, 8, 5); // cell with value 5

    ProgressEventList expectedList;
    expectedList.length = 1;
    expectedList.items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->newNotes[5] = 0; // expecting the value 5 to no longer be a candidate
    expectedList.items[0]->strategyName = strdup("noDuplicatesStrategy");

    // act
    ProgressEventList *actualList = noDuplicatesStrategy(grid, 0, 0);

    // assert
    ASSERT_EQ((*grid)[0][0]->notes[5], 0) << "The cell should no longer be a candidate for the value 5.";
    assertProgressEventListsMatch(&expectedList, actualList);
}

TEST(noDuplicatesStrategy, ShouldRemoveCandidateAndReturnProgressEvent_IfColumnHasValue) {
    // arrange
    Grid *grid = createEmptyGrid();
    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve
    (*grid)[8][0] = createCell(8, 0, 5); // cell with value 5

    ProgressEventList expectedList;
    expectedList.length = 1;
    expectedList.items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
    expectedList.items[0] = createTemplateProgressEvent();
    expectedList.items[0]->newNotes[5] = 0; // expecting the value 5 to no longer be a candidate
    expectedList.items[0]->strategyName = strdup("noDuplicatesStrategy");

    // act
    ProgressEventList *actualList = noDuplicatesStrategy(grid, 0, 0);

    // assert
    ASSERT_EQ((*grid)[0][0]->notes[5], 0) << "The cell should no longer be a candidate for the value 5.";
    assertProgressEventListsMatch(&expectedList, actualList);
}

//TEST(noDuplicatesStrategy, ShouldReturnProgressEventIfBlockHasValue) {
//    // arrange
//    Grid *grid = createEmptyGrid();
//    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve
//    (*grid)[2][2] = createCell(2, 2, 5); // cell with value
//
//    ProgressEvent expected;
//    expected.strategyName = strdup("noDuplicatesStrategy");
//    expected.row = 0;
//    expected.col = 0;
//    expected.oldValue = 0;
//    expected.newValue = 0;
//    for(int i = 0; i <= MAX_VAL; i++) {
//        if (i == 0) { // notes at [0] is always 0
//            expected.oldNotes[i] = 0;
//            expected.newNotes[i] = 0;
//        } else {
//            expected.oldNotes[i] = 1;
//            expected.newNotes[i] = 1;
//        }
//    }
//    expected.newNotes[5] = 0;
//
//    // act
//    ProgressEvent *actual = noDuplicatesStrategy(grid, 0, 0);
//
//    // assert
//    ASSERT_TRUE(progressEventsAreEqual(&expected, actual));
//
//}
//
//TEST(noDuplicatesStrategy, ShouldReturnNullIfNoProgressWasMade) {
//    // arrange
//    Grid *grid = createEmptyGrid();
//    (*grid)[0][0] = createCell(0, 0, 0); // cell to solve
//    (*grid)[3][3] = createCell(3, 3, 5); // cell with value (not in cell-to-solve's units)
//
//    ProgressEvent *expected = nullptr;
//
//    // act
//    ProgressEvent *actual = noDuplicatesStrategy(grid, 0, 0);
//
//    // assert
//    ASSERT_EQ(expected, actual);
//
//}
