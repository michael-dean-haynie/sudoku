#include <stdio.h>
#include <stdlib.h>
#include "cell.h"


Cell *createCell(int row, int col, int value) {
    Cell *cell = (Cell *) malloc(sizeof(Cell));
    cell->row = row;
    cell->col = col;
    cell->value = value;

    // initialize notes
    for (int n = 0; n <= MAX_VAL; n++) {
        if (value != 0) {
            cell->notes[n] = (n == value) ? 1 : 0;
        } else {
            cell->notes[n] = (n == 0) ? 0 : 1;
        }
    }

    return cell;
}

void freeCell(Cell *cell) {
    free(cell);
}

void printCellData(Cell *cell) {
    printf("Logging cell at (%d,%d):\n", cell->row, cell->col);
    printf("  value: %d\n", cell->value);
    printf("  notes: ");
    printNotes(cell->notes);
    // printCellNotesDetailed(cell);
}

void printNotes(const int notes[]) {
    for (int i = 1; i <= MAX_VAL; i++) {
        int note = notes[i];
        if (note == 1) {
            printf("%d", i);
        } else {
            printf("_");
        }
        if (i < MAX_VAL) {
            printf(" ");
        }
    }
    printf("\n");
}

void printCellNotesDetailed(Cell *cell) {
    printf("  notes: 0 1 2 3 4 5 6 7 8 9\n");
    printf("         -------------------\n");
    printf("         ");
    for (int i = 0; i <= MAX_VAL; i++) {
        printf("%d", cell->notes[i]);
        if (i < MAX_VAL) {
            printf(" ");
        }
    }
    printf("\n");
}

void setCellValue(Cell *cell, int value) {
    cell->value = value;
    for (int i = 0; i <= MAX_VAL; ++i) {
        cell->notes[i] = 0;
    }
    cell->notes[value] = 1;
}

void freeCellList(CellList *cellList) {
    // free list of pointers
    free(cellList->items);

    // free CellList, itself
    free(cellList);
}