#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "naked-single.h"

ProgressEvent *nakedSingleStrat(Grid *grid_p, int row, int col) {
    Cell *cell = (*grid_p)[row][col];
    if (cell->value != 0) {
        return NULL; // do not process cells already solved
    }

    int candidateCount = 0;
    int lastCandidate = 0;
    for (int ni = MIN_VAL; ni <= MAX_VAL; ni++) { // notes index
        if (cell->notes[ni] == 1) {
            candidateCount++;
            lastCandidate = ni;
            if (candidateCount >= 2) {
                break; // short circuit if this is the second candidate found
            }
        }
    }

    if (candidateCount == 1) {
        char *funcName = malloc(strlen(__func__) + 1);
        strcpy(funcName, __func__);
        ProgressEvent *pe = prepProgressEvent(cell, funcName);
        cell->value = lastCandidate;
        updateProgressEvent(pe, cell);

        return pe;
    }

    // return null pointer if no progress was made
    return NULL;
}