#include <string.h>
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

ProgressEvent *createTemplateProgressEvent(void) {
    ProgressEvent *pe = (ProgressEvent*) malloc(sizeof(ProgressEvent));
    pe->strategyName = strdup("DEFAULT TEMPLATE VALUE");
    pe->row = 0;
    pe->col = 0;
    pe->oldValue = 0;
    pe->newValue = 0;
    for(int i = 0; i <= MAX_VAL; i++) {
        if (i == 0) { // notes at [0] is always 0
            pe->oldNotes[i] = 0;
            pe->newNotes[i] = 0;
        } else { // all other values are candidates by default
            pe->oldNotes[i] = 1;
            pe->newNotes[i] = 1;
        }
    }
    return pe;
}