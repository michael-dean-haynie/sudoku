#pragma once
#include "cell.h"
#include "grid.h"

typedef struct ProgressEvent {
    char *strat_p;
    int row;
    int col;
    int oldValue;
    int newValue;
    int oldNotes[MAX_VAL + 1];
    int newNotes[MAX_VAL + 1];
} ProgressEvent;

ProgressEvent* prepProgressEvent(Cell *cell_p, char *strat_p);
void updateProgressEvent(ProgressEvent *pe_p, Cell *cell_p);
void freeProgressEvent(ProgressEvent *pe_p);
void printProgressEvent(ProgressEvent *pe_p);
void updateConsoleLive(Grid *grid_p);
int progressEventsAreEqual(ProgressEvent *pe1, ProgressEvent *pe2);