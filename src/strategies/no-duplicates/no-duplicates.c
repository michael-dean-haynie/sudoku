#include <stdlib.h>
#include <string.h>
#include "no-duplicates.h"
#include "unit.h"

ProgressEventList *noDuplicatesStrat(Grid *grid_p, int row, int col) {
    ProgressEventList *result = (ProgressEventList*) malloc(sizeof(ProgressEventList));
    result->length = 0;

    Cell *cellToSolve = (*grid_p)[row][col];
    if (cellToSolve->value != 0) {
       return result; // do not process cells already solved
    }

    Unit *units[3] = {
            getRowUnit(grid_p, row, col),
            getColumnUnit(grid_p, row, col),
            getBlockUnit(grid_p, row, col),
    };

    for (int i = 0; i < 3; i++) {
        Unit *unit = units[i];
        for (int ci = 0; ci < UNIT_SIZE; ci++) { // cell index
            Cell *cell = (*unit)[ci];
            if (cell->row == row && cell->col == col) {
                continue; // don't compare target cell against itself
            }
            if (cell->value && cellToSolve->notes[cell->value]) {
                char *funcName = malloc(strlen(__func__) + 1);
                strcpy(funcName, __func__);
                ProgressEvent *pe_p = prepProgressEvent(cellToSolve, funcName);
                cellToSolve->notes[cell->value] = 0;
                updateProgressEvent(pe_p, cellToSolve);

                // free units
                for (int ui = 0; ui < 3; ui++) { // units index
                    freeUnit(units[ui]);
                }

                // return at first progress event
                result->length++;
                result->items = (ProgressEvent**) malloc(sizeof(ProgressEvent*) * result->length);
                result->items[0] = pe_p;
                return result;
            }
        }
    }

    // free units
    for (int ui = 0; ui < 3; ui++) { // units index
        freeUnit(units[ui]);
    }

    // return null pointer if no progress was made
    return result;
}