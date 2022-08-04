#include <stdio.h>
#include "grid.h"
#include "unit.h"
#include "execute-strategies.h"

int main(void) {
    printf("the app is running :)\n");

    Grid *grid_p = loadGridFromStdin();
    printGrid(grid_p);

    while(1) {
        int progressWasMade = 0;
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                Cell *cell = (*grid_p)[row][col];
                if (executeStrategies(grid_p, row, col)) {
                    progressWasMade = 1;
                }
            }
        }

        if (!progressWasMade) {
            break; // stop if no progress was made on any cell
        }
    }
    // printGrid(grid_p);
    printf("damn, i'm good\n");

    freeGrid(grid_p);
    return 0;
}