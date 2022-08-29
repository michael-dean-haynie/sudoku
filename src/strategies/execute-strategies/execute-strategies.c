#include <stdlib.h>
#include "execute-strategies.h"
#include "progress-event.h"
#include "no-duplicates.h"
#include "naked-single.h"
#include "hidden-single.h"

int executeStrategies(Grid *grid_p, int row, int col, int slowMode) {
    // initialize an array of strategy functions that return ProgressEvent*
    ProgressEventList *(*strats[])(Grid *grid_p, int row, int col) = {
            noDuplicatesStrategy,
            nakedSingleStrategy,
            hiddenSingleStrategy,
    };

    int stratCount = sizeof strats / sizeof strats[0];

    int cellMadeProgress = 0;
    int stratMadeProgress = 0;
    for (int si = 0; si < stratCount; si++) {
        ProgressEventList *pel = strats[si](grid_p, row, col);
        if (pel != NULL && pel->length > 0) {
            stratMadeProgress = 1;
            cellMadeProgress = 1;

            if (slowMode) {
                for (int evtIdx = 0; evtIdx < pel->length; ++evtIdx) { // event index
                    printProgressEvent(pel->items[evtIdx]);
                    updateConsoleLive(grid_p);
                }
            }

            freeProgressEventList(pel);
        }

        if (stratMadeProgress) {
            stratMadeProgress = 0;
            si = -1; // start over with first strategy
        }
    }

    return cellMadeProgress;
}
