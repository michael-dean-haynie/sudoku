#include "cell.h"
#include "grid.h"

#define UNIT_SIZE 9 // number of cells in a unit

// Unit: An array of Cell pointers (a row, col, or block)
typedef Cell *(Unit[UNIT_SIZE]);

// Does not free cells of unit, just the array of pointers
void freeUnit(Unit *unit_p);

// Unit-related functions
Unit* getRowUnit(Grid *grid_p, int row, int col);
Unit* getColumnUnit(Grid *grid_p, int row, int col);
Unit* getBlockUnit(Grid *grid_p, int row, int col);

void printUnitData(Unit *unit_p);