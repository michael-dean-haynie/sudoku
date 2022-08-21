#include <gtest/gtest.h>

extern "C" {
#include "unit.h"
#include "cell.h"
#include "test-helpers.h"
}

TEST(UnitTests, GetUnitCandidatesForValueShouldReturnMultipleCells) {
    // arrange
    Unit *unit_p = createEmptyUnit();

    // act
   CellList *result = getUnitCandidatesForValue(unit_p, 5);

    // assert
    EXPECT_EQ(result->length, 9);
}

TEST(UnitTests, GetUnitCandidatesForValueShouldReturnSingleCell) {
    // arrange
    Unit *unit_p = createEmptyUnit();
    for (int ui = 0; ui < UNIT_SIZE; ++ui) {
        if (ui != 0) { // remove all but 1 candidates
            Cell *cell = (*unit_p)[ui];
            cell->notes[5] = 0;
        }
    }

    // act
    CellList *result = getUnitCandidatesForValue(unit_p, 5);

    // assert
    EXPECT_EQ(result->length, 1);
    EXPECT_EQ(result->items[0]->row, (*unit_p)[0]->row);
    EXPECT_EQ(result->items[0]->col, (*unit_p)[0]->col);
}