#include <stdlib.h>
#include "unit.h"

void freeUnit(Unit *unit_p) {
    free(unit_p);
}

Unit *getRowUnit(Grid *grid_p, int row, __attribute__((unused)) int col) {
    Unit *unit_p = malloc(sizeof(Unit));
    for (int c = 0; c < COLS; c++) {
        (*unit_p)[c] = (*grid_p)[row][c];
    }
    return unit_p;
}

Unit *getColumnUnit(Grid *grid_p, int row, int col) {
    Unit *unit_p = malloc(sizeof(Unit));
    for (int r = 0; r < COLS; r++) {
        (*unit_p)[r] = (*grid_p)[r][col];
    }
    return unit_p;
}

Unit *getBlockUnit(Grid *grid_p, int row, int col) {
    Unit *unit_p = malloc(sizeof(Unit));
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    int unitIndex = 0;
    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            (*unit_p)[unitIndex++] = (*grid_p)[r][c];
        }
    }
    return unit_p;
}

void printUnitData(Unit *unit_p) {
    for (int i = 0; i < UNIT_SIZE; i++) {
        printCellData((*unit_p)[i]);
    }
}

CellList *getUnitCandidatesForValue(Unit *unit_p, int value) {
    int candidates[UNIT_SIZE];
    int ci = 0;

    for (int ui = 0; ui < UNIT_SIZE; ++ui) {
      Cell *cell = (*unit_p)[ui];
      if (cell->notes[value] == 1) {
          candidates[ci++] = ui;
      }
    }

    CellList *cellList = (CellList*) malloc(sizeof(CellList));
    cellList->length = ci;
    cellList->items = (Cell**) malloc(ci * sizeof(Cell*));
    for (int i = 0; i < ci; ++i) {
        cellList->items[i] = (*unit_p)[candidates[i]];
    }
    return cellList;
}
