#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grid.h"
#include "progress-event.h"

ProgressEvent *prepProgressEvent(Cell *cell_p, char *strat_p) {
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

void updateConsoleLive(Grid *grid_p) {
    printGrid(grid_p);
    printPercentComplete(grid_p);

    // wait for 50 ms
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 50 * 1000000;
    nanosleep(&ts, NULL);
}

int progressEventsAreEqual(ProgressEvent *pe1, ProgressEvent *pe2) {
    for (int i = 0; i <= MAX_VAL; i++) {
        if (pe1->oldNotes[i] != pe2->oldNotes[i]) {
            return 0;
        }

        if (pe1->newNotes[i] != pe2->newNotes[i]) {
            return 0;
        }
    }

    return
            strcmp(pe1->strat_p, pe2->strat_p) == 0
            && pe1->row == pe2->row
            && pe1->col == pe2->col
            && pe1->oldValue == pe2->oldValue
            && pe1->newValue == pe2->newValue;
}
