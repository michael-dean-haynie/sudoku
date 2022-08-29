#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "naked-pair.h"
#include "unit.h"
#include "progress-event.h"

ProgressEventList *nakedPairStrategy(Grid *grid, int row, int col) {
    // initialize result
    ProgressEventList *result = (ProgressEventList *) malloc(sizeof(ProgressEventList));
    result->length = 0;

    // initialize ProgressEvent Temporary Array
    ProgressEvent *peTempArray[MAX_EVENTS];
    int peTempArrayLength = 0;

    Cell *cellToSolve = (*grid)[row][col];

    // check for early exit conditions
    int cellIsSolved = cellToSolve->value != 0;

    int noteCount = 0;
    for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
        if (cellToSolve->notes[noteIdx] == 1) {
            noteCount++;
        }
    }
    int cellHasExactly2Notes = noteCount == 2;

    if (cellIsSolved || !cellHasExactly2Notes) {
        return result; // no progress to be made
    }

    // process each unit
    Unit *units[3] = {
            getRowUnit(grid, row, col),
            getColumnUnit(grid, row, col),
            getBlockUnit(grid, row, col),
    };

    for (int unitsIdx = 0; unitsIdx < 3; ++unitsIdx) {
        Unit *unit = units[unitsIdx];

        // search for cell in unit with exact same 2 notes
        Cell *matchingCell = NULL;
        for (int unitIdx = 0; unitIdx < UNIT_SIZE; ++unitIdx) {
            Cell *cell = (*unit)[unitIdx];

            // skip cell if it is the cell to solve
            if (cell->row == cellToSolve->row && cell->col == cellToSolve->col) {
                continue;
            }

            int cellNotesMatch = 1;
            for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
                if (cell->notes[noteIdx] != cellToSolve->notes[noteIdx]) {
                    cellNotesMatch = 0;
                    break;
                }
            }
            if (cellNotesMatch) {
                matchingCell = cell;
                break;
            }
        }

        // move on to next unit if no matching cell was found in this one
        if (!matchingCell) {
            continue;
        }

        // update any other cells in unit that were also candidates for one of the 2 values
        for (int unitIdx = 0; unitIdx < UNIT_SIZE; ++unitIdx) {
            Cell *cell = (*unit)[unitIdx];

            // skip cell if it is one of the matching pair
            int cellIsOneOfThePair =
                    (cell->col == cellToSolve->col && cell->row == cellToSolve->row) ||
                    (cell->col == matchingCell->col && cell->row == matchingCell->row);
            if (cellIsOneOfThePair) {
                continue;
            }

            // update cell if needed
            ProgressEvent *pe = NULL;
            for (int noteIdx = MIN_VAL; noteIdx <= MAX_VAL; ++noteIdx) {
                if (cell->notes[noteIdx] == 1 && cellToSolve->notes[noteIdx] == 1) {
                    // initialize progress event (if it hasn't already been for this cell)
                    if (!pe) {
                        char *funcName = malloc(strlen(__func__) + 1);
                        strcpy(funcName, __func__);
                        pe = prepProgressEvent(cell, funcName);
                    }

                    // update the cell
                    cell->notes[noteIdx] = 0;
                }
            }

            // update and save ProgressEvent if needed
            if (pe) {
                updateProgressEvent(pe, cell);
                peTempArray[peTempArrayLength++] = pe;
            }
        }
    }

    // add any progress events from temp array to result list and return it
    result->length = peTempArrayLength;
    if (peTempArrayLength > 0) {
        result->items = (ProgressEvent **) malloc(peTempArrayLength * sizeof(ProgressEvent *));
        for (int tempIdx = 0; tempIdx < peTempArrayLength; ++tempIdx) {
            result->items[tempIdx] = peTempArray[tempIdx];
        }
    }

    return result;
}
