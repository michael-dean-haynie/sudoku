#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grid.h"
#include "progress-event.h"

ProgressEvent *prepProgressEvent(Cell *cell, char *strategyName) {
    static int number = 0;

    ProgressEvent *pe = malloc(sizeof(ProgressEvent));
    pe->number = ++number; // chronological id
    pe->strategyName = strategyName;
    pe->row = cell->row;
    pe->col = cell->col;
    pe->oldValue = cell->value;
    memcpy(&pe->oldNotes, &cell->notes, sizeof(cell->notes));
    return pe;
}

void updateProgressEvent(ProgressEvent *pe_p, Cell *cell_p) {
    pe_p->newValue = cell_p->value;
    memcpy(&pe_p->newNotes, &cell_p->notes, sizeof(cell_p->notes));
}

void freeProgressEvent(ProgressEvent *pe_p) {
    // free string (char *)
    free(pe_p->strategyName);

    // free progress event pointer, itself
    free(pe_p);
}

void printProgressEvent(ProgressEvent *pe_p) {
    printf("progress made on cell at (%d,%d):\n", pe_p->row, pe_p->col);
    printf("  number:   %d\n", pe_p->number);
    printf("  strategy: %s\n", pe_p->strategyName);
    printf("  oldValue: %d\n", pe_p->oldValue);
    printf("  newValue: %d\n", pe_p->newValue);
    printf("  oldNotes: ");
    printNotes(pe_p->oldNotes);
    printf("  newNotes: ");
    printNotes(pe_p->newNotes);
}

void updateConsoleLive(Grid *grid_p, ProgressEvent *pe) {
    printProgressEvent(pe); // 7 lines
    printGrid(grid_p); // 37 lines
    printPercentComplete(grid_p); // 1 line

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
            strcmp(pe1->strategyName, pe2->strategyName) == 0
            && pe1->row == pe2->row
            && pe1->col == pe2->col
            && pe1->oldValue == pe2->oldValue
            && pe1->newValue == pe2->newValue;
}

void freeProgressEventList(ProgressEventList *list) {
    for (int itemIdx = 0; itemIdx < list->length; ++itemIdx) {
        free(list->items[itemIdx]);
    }
    free(list->items);
    free(list);
}