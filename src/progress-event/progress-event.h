#pragma once

#include "cell.h"
#include "grid.h"

// the maximum number of ProgressEvents returnable from any single strategy execution
// at best each cell in the row/col/block will be updated: 9 + 8 + 4 (no duplicates)
#define MAX_EVENTS 21

typedef struct ProgressEvent {
    char *strategyName;
    int row;
    int col;
    int oldValue;
    int newValue;
    int oldNotes[MAX_VAL + 1];
    int newNotes[MAX_VAL + 1];
} ProgressEvent;



ProgressEvent *prepProgressEvent(Cell *cell_p, char *strat_p);

void updateProgressEvent(ProgressEvent *pe_p, Cell *cell_p);

void freeProgressEvent(ProgressEvent *pe_p);

void printProgressEvent(ProgressEvent *pe_p);

void updateConsoleLive(Grid *grid_p);

int progressEventsAreEqual(ProgressEvent *pe1, ProgressEvent *pe2);

typedef struct ProgressEventList {
    int length;
    ProgressEvent **items;
} ProgressEventList;

/**
 * Free ProgressEventList by freeing its items member, the 'items' member, and then its self
 * @param list the ProgressEventList to free
 */
void freeProgressEventList(ProgressEventList *list);