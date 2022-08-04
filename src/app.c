#include <stdio.h>
#include "grid.h"

int main(void) {
    printf("the app is running :)\n");

    Grid *grid_p = loadGridFromStdin();
    printGridData(grid_p);
    printGrid(grid_p);

    freeGrid(grid_p);
    return 0;
}