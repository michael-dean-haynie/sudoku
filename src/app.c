#include <stdio.h>
#include "grid.h"
#include "unit.h"

int main(void) {
    printf("the app is running :)\n");

    Grid *grid_p = loadGridFromStdin();
    printGrid(grid_p);

    Unit *unit_p = getRowUnit(grid_p, 4, 4);
    printUnitData(unit_p);
    freeUnit(unit_p);
    unit_p = getColumnUnit(grid_p, 4, 4);
    printUnitData(unit_p);
    freeUnit(unit_p);
    unit_p = getBlockUnit(grid_p, 4, 4);
    printUnitData(unit_p);
    freeUnit(unit_p);

    freeGrid(grid_p);
    return 0;
}