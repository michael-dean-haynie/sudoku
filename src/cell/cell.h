#pragma once
#define MIN_VAL 1 // the minimum value of a solved cell
#define MAX_VAL 9 // the maximum value of a solved cell

// A single cell on a sudoku board
typedef struct Cell {
    int value;
    // so to easily access notes by value index (1-9)
    int notes[MAX_VAL + 1];
    int row;
    int col;
} Cell;

// Cell-related functions
Cell* createCell(int row, int col, int value);
void freeCell(Cell *cell);

void printCellData(Cell *cell);
void printCellNotes(Cell *cell);
void printCellNotesDetailed(Cell *cell);