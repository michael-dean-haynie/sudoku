#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "progress-event.h"
#include "unit.h"

ProgressEventList * hiddenSingleStrategy(Grid *grid_p, int row, int col) {
    ProgressEventList *result = (ProgressEventList *) malloc(sizeof(ProgressEventList));
    result->length = 0;

    Cell *cellToSolve = (*grid_p)[row][col];
    if (cellToSolve->value != 0) {
        return result; // do not process cells already solved
    }

    Unit *units[3] = {
            getRowUnit(grid_p, row, col),
            getColumnUnit(grid_p, row, col),
            getBlockUnit(grid_p, row, col),
    };

    for (int candidateVal = MIN_VAL; candidateVal <= MAX_VAL ; ++candidateVal) {
       // skip non-candidates
       if(cellToSolve->notes[candidateVal] == 0) {
           continue;
       }

       // try each unit
        for (int ui = 0; ui < 3; ++ui) {
            Unit *unit_p = units[ui];
            CellList *candidateCells = getUnitCandidatesForValue(unit_p, candidateVal);

            if (candidateCells->length == 1) {
                // create Progress event
                Cell *cell = candidateCells->items[0];
                char *funcName = malloc(strlen(__func__) + 1);
                strcpy(funcName, __func__);
                ProgressEvent *pe = prepProgressEvent(cell, funcName);
                setCellValue(cell, candidateVal);
                updateProgressEvent(pe, cell);

                // free cell list
                freeCellList(candidateCells);

                // return progress event
                freeUnit(units[0]);
                freeUnit(units[1]);
                freeUnit(units[2]);

                result->length++;
                result->items = (ProgressEvent **) malloc(sizeof(ProgressEvent *));
                result->items[0] = pe;
                return result;

            } else {
                freeCellList(candidateCells);
            }
        }
    }

    freeUnit(units[0]);
    freeUnit(units[1]);
    freeUnit(units[2]);
    return result; // no progress made
}