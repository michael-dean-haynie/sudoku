#pragma once
#include "grid.h"

/** returns 1 if progress was made on cell, 0 otherwise */
int executeStrategies(Grid *grid_p, int row, int col, int slowMode);