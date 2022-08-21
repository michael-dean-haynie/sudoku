#include "test-helpers.h"
#include "grid.h"
#include "cell.h"

Grid *createEmptyGrid(void) {
    Grid *grid_p = (Grid *) malloc(sizeof(Grid));
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            (*grid_p)[row][col] = createCell(row, col, 0);
        }
    }
    return grid_p;
}

Unit *createEmptyUnit(void) {
    Unit *unit_p = (Unit *) malloc(sizeof(Unit));
    for (int ui = 0; ui < UNIT_SIZE; ++ui) {
        int column = ui; // not important
        (*unit_p)[ui] = createCell(0, column, 0);
    }
    return unit_p;
}