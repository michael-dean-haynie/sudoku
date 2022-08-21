#pragma once

#include "cell.h"
#include "grid.h"

#define UNIT_SIZE 9 // number of cells in a unit

// Unit: An array of Cell pointers (a row, col, or block)
typedef Cell *(Unit[UNIT_SIZE]);

// Does not free cells of unit, just the array of pointers
void freeUnit(Unit *unit_p);

// Unit-related functions
Unit *getRowUnit(Grid *grid_p, int row, __attribute__((unused)) int col);

Unit *getColumnUnit(Grid *grid_p, int row, int col);

Unit *getBlockUnit(Grid *grid_p, int row, int col);

void printUnitData(Unit *unit_p);

/**
 * Get a CellList of cells in a unit that are candidates for the provided value.
 * The CellList is allocated on the heap - take care to free it.
 *
 * @param unit_p a pointer to the unit
 * @param value the value to check for
 * @return a pointer the newly allocated CellList
 */
CellList *getUnitCandidatesForValue(Unit *unit_p, int value);