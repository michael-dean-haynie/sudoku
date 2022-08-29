#include <stdio.h>
#include <string.h>
#include "grid.h"
#include "execute-strategies.h"

int main(int argc, char *argv[]) {
    // parse arguments
    int slowMode = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--slow") == 0) {
                slowMode = 1;
            }
        }
    }


    Grid *grid_p = loadGridFromStdin();

    printf("\nInitial State:\n");
    printGrid(grid_p);
    printPercentComplete(grid_p);
    printf("\n");

    while (1) {
        int progressWasMade = 0;
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                if (executeStrategies(grid_p, row, col, slowMode)) {
                    progressWasMade = 1;
                }
            }
        }

        if (!progressWasMade) {
            break; // stop if no progress was made on any cell
        }
    }

    printf("\nFinal State:\n");
    printGrid(grid_p);
    printPercentComplete(grid_p);

    freeGrid(grid_p);
    return 0;
}