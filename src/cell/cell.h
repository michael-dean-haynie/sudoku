#pragma once
#define MIN_VAL 1 // the minimum value of a solved cell
#define MAX_VAL 9 // the maximum value of a solved cell

/**
 * A single cell on a sudoku board
 */
typedef struct Cell {
    int value;
    // so to easily access notes by value index (1-9)
    int notes[MAX_VAL + 1];
    int row;
    int col;
} Cell;

Cell *createCell(int row, int col, int value);

void freeCell(Cell *cell);

void printCellData(Cell *cell);

void printNotes(const int notes[]);

void printCellNotesDetailed(Cell *cell);

/**
 * Sets the value for a cell, also updates the cell's notes
 * @param cell a pointer to the cell to update
 * @param value a integer value to update the cell with
 */
void setCellValue(Cell *cell, int value);

/**
 * A struct for a dynamic-length list of cells.
 */
typedef struct CellList {
    int length;
    Cell **items;
} CellList;

void freeCellList(CellList *cellList);