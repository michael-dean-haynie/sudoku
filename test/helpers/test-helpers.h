#include <stdlib.h>
#include "grid.h"
#include "unit.h"
#include "progress-event.h"

/**
 * Allocates a 9x9 sudoku grid with all 81 cells.
 * Each cell has a value of zero and each cell is a candidate for values 1-9.
 * @return a pointer to the newly allocated grid.
 */
Grid *createEmptyGrid(void);

Unit *createEmptyUnit(void);