#include <stdlib.h>
#include "execute-strategies.h"
#include "progress-event.h"
#include "naked-single.h"
#include "no-duplicates.h"

int executeStrategies(Grid *grid_p, int row, int col) {
    // initialize an array of strategy functions that return ProgressEvent*
    ProgressEvent* (*strats[])(Grid *grid_p, int row, int col) = {
        nakedSingleStrat,
        noDuplicatesStrat
    };

    int stratCount = sizeof strats / sizeof strats[0];

    int cellMadeProgress = 0;
    int stratMadeProgress = 0;
    for (int si = 0; si < stratCount; si++) {
        ProgressEvent* pe = strats[si](grid_p, row, col);
        if (pe != NULL) {
            stratMadeProgress = 1;
            cellMadeProgress = 1;
            printProgressEvent(pe);
            freeProgressEvent(pe);
            updateConsoleLive(grid_p);
        }

        if (stratMadeProgress) {
            stratMadeProgress = 0;
            si = -1; // start over with first strategy
        }
    }

    return cellMadeProgress;
}
