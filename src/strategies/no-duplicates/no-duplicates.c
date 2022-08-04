#include "no-duplicates.h"
#include "unit.h"

void noDuplicatesStrat(Grid *grid_p, int row, int col) {
    Cell *cellToSolve = (*grid_p)[row][col];
    Unit *units[3] = {
        getRowUnit(grid_p, row, col),
        getColumnUnit(grid_p, row, col),
        getBlockUnit(grid_p, row, col),
    };

    for (int i = 0; i < 3; i ++) {
        Unit *unit = units[i];
        for(int ci = 0; ci < UNIT_SIZE; ci++) { // cell index
            Cell *cell = (*unit)[ci];
            if(cell->row == row && cell->col == col) {
                continue; // don't compare target cell against itself
            }
            if (cell->value && cellToSolve->notes[cell->value]) {
                cellToSolve->notes[cell->value] = 0;
                // TODO: save progress event
            }
        }
    }

    // free units
    for (int i = 0; i < 3; i++) {
        freeUnit(units[i]);
    }
}