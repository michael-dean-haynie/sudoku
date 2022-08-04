#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "cell.h"

Grid* loadGridFromStdin() {
    Grid *grid_p = malloc(sizeof(Grid));
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            char strVal[2] = { fgetc(stdin), '\0' };
            int intVal = atoi(strVal);
            if (intVal < 0 || intVal > 9) {
                intVal = 0;
            }
            (*grid_p)[row][col] = createCell(row, col, intVal);
        }
        fgetc(stdin); // move past line break
    }

    return grid_p;
}

void freeGrid(Grid *grid_p) {
    // free each cell pointer
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            freeCell((*grid_p)[row][col]);
        }
    }

    // free grid, itself
    free(grid_p);
}

void printGrid(Grid *grid_p) {
    int totalRows = (4 * 9) + 1;
    int totalCols = (4 * 9) + 1;
    for (int row = 0; row < totalRows; row++) {
        int gridRow = row / 4;
        int noteRow = row % 4;
        int isHorizontal = noteRow == 0;
        for (int col = 0; col < totalCols; col++) {
            int gridCol = col / 4;
            int noteCol = col % 4;
            int isVertical = noteCol == 0;
            if (isHorizontal && isVertical) {
                printf("+");
            } else if (isHorizontal) {
                printf("-");
            } else if (isVertical) {
                printf("|");
            } else {
                printNoteOrValue(grid_p, gridRow, gridCol, noteRow, noteCol);
            }
        }
        printf("\n");
    }
}

void printNoteOrValue(Grid *grid_p, int gridRow, int gridCol, int noteRow, int noteCol) {
    Cell *cell = (*grid_p)[gridRow][gridCol];
    int noteIndex = ((noteRow - 1) * 3) + noteCol;
    if (cell->value != 0) {
        if (noteIndex == 5) { // center
            printf("%d", cell->value);
        } else {
            printf(" ");
        }
    } else if (cell->notes[noteIndex]) {
        printf("%d", noteIndex);
    } else {
        printf(" ");
    }
}

void printGridData(Grid *grid_p) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            printCellData((*grid_p)[row][col]);
        }
    }
}