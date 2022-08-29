#include <stdlib.h>
#include <string.h>
#include "naked-single.h"

ProgressEventList *nakedSingleStrategy(Grid *grid_p, int row, int col) {
    ProgressEventList *result = (ProgressEventList *) malloc(sizeof(ProgressEventList));
    result->length = 0;

    Cell *cell = (*grid_p)[row][col];
    if (cell->value != 0) {
        return result; // do not process cells already solved
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

        result->length++;
        result->items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
        result->items[0] = pe;
        return result;
    }

    // return null pointer if no progress was made
    return result;
}