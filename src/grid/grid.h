#pragma once

#include "cell.h"

#define ROWS 9 // number of rows in a grid
#define COLS 9 // number of columns in a grid

// Grid: a 9x9 2-dimensional array of cell pointers
typedef Cell *(Grid[ROWS][COLS]);

// Grid-related functions
Grid *loadGridFromStdin();

void freeGrid(Grid *grid);

void printGrid(Grid *grid_p);

void printGridData(Grid *grid_p);

void printNoteOrValue(Grid *grid_p, int gridRow, int gridCol, int noteRow, int noteCol);

void printPercentComplete(Grid *grid_p);