#include <stdio.h>
#include "grid.h"
#include "unit.h"
#include "no-duplicates.h"

int main(void) {
    printf("the app is running :)\n");

    Grid *grid_p = loadGridFromStdin();
    printGrid(grid_p);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            noDuplicatesStrat(grid_p, row, col);
        }
    }
    printGrid(grid_p);

    freeGrid(grid_p);
    return 0;
}