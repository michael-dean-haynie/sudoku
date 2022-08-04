#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "progress-event.h"

ProgressEvent* prepProgressEvent(Cell *cell_p, char *strat_p) {
    ProgressEvent *pe_p = malloc(sizeof(ProgressEvent));
    pe_p->strat_p = strat_p;
    pe_p->row = cell_p->row;
    pe_p->col = cell_p->col;
    pe_p->oldValue = cell_p->value;
    memcpy(&pe_p->oldNotes, &cell_p->notes, sizeof(cell_p->notes));
    return pe_p;
}

void updateProgressEvent(ProgressEvent *pe_p, Cell *cell_p) {
    pe_p->newValue = cell_p->value;
    memcpy(&pe_p->newNotes, &cell_p->notes, sizeof(cell_p->notes));
}

void freeProgressEvent(ProgressEvent *pe_p) {
    // free string (char *)
    free(pe_p->strat_p);

    // free progress event pointer, itself
    free(pe_p);
}

void printProgressEvent(ProgressEvent *pe_p) {
    printf("progress made on cell at (%d,%d):\n", pe_p->row, pe_p->col);
    printf("  strategy: %s\n", pe_p->strat_p);
    printf("  oldValue: %d\n", pe_p->oldValue);
    printf("  newValue: %d\n", pe_p->newValue);
    printf("  oldNotes: ");
    printNotes(pe_p->oldNotes);
    printf("  newNotes: ");
    printNotes(pe_p->newNotes);
}