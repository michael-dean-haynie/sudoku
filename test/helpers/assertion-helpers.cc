#include "assertion-helpers.h"
#include <gtest/gtest.h>

extern "C" {
#include "progress-event.h"
}

void assertProgressEventsMatch(ProgressEvent *expected, ProgressEvent *actual) {
    ASSERT_STREQ(expected->strategyName, actual->strategyName) << "strategyNames should match";
    ASSERT_EQ(expected->row, actual->row) << "rows should match";
    ASSERT_EQ(expected->col, actual->col) << "cols should match";
    ASSERT_EQ(expected->oldValue, actual->oldValue) << "oldValues should match";
    ASSERT_EQ(expected->newValue, actual->newValue) << "newValues should match";
    ASSERT_EQ(expected->newValue, actual->newValue) << "newValues should match";
    for (int noteIdx = 0; noteIdx <= MAX_VAL; ++noteIdx) {
        char* msg;

        // check oldNotes match at index
        asprintf(&msg, "oldNotes[%d] should match", noteIdx);
        ASSERT_EQ(expected->oldNotes[noteIdx], actual->oldNotes[noteIdx]) << msg;
        free(msg);

        // check new notes match at index
        asprintf(&msg, "newNotes[%d] should match", noteIdx);
        ASSERT_EQ(expected->newNotes[noteIdx], actual->newNotes[noteIdx]) << msg;
        free(msg);
    }
}

void assertProgressEventListsMatch(ProgressEventList *expected, ProgressEventList *actual) {
    ASSERT_EQ(expected->length, actual->length) << "lengths should match";

    // exit early if lengths are zero (don't need to do anything else)
    if (actual->length == 0) {
        return;
    }

    // List order should not matter - just need to have a 1:1 match.
    // Track the corresponding indexes of matches in either list. -1 signifies match has not been found.
    int expectedItemHasMatch[MAX_EVENTS];
    memset(expectedItemHasMatch, -1, sizeof(int) * expected->length);

    int actualItemHasMatch[MAX_EVENTS];
    memset(actualItemHasMatch, -1, sizeof(int) * actual->length);

    // Check that there is a matching "actual" item for every "expected" item
    for (int expIdx = 0; expIdx < expected->length; ++expIdx) {
        ProgressEvent *expectedItem = expected->items[expIdx];

        for (int actIdx = 0; actIdx < actual->length; ++actIdx) {
            ProgressEvent *actualItem = actual->items[actIdx];

            int isRowColMatch = (expectedItem->row == actualItem->row) && (expectedItem->col == actualItem->col);
            if (isRowColMatch) {
                expectedItemHasMatch[expIdx] = actIdx;
                actualItemHasMatch[actIdx] = expIdx;

                assertProgressEventsMatch(expectedItem, actualItem);
                break; // move on to next expected item
            }
        }
    }

    // Check that there are no unmatched items (-1) in either list
    for (int i = 0; i < expected->length; ++i) {
        char* msg;
        asprintf(&msg, "expected items list should not have an unmatched item at index [%d]", i);
        ASSERT_NE(expectedItemHasMatch[i], -1) << msg;
        free(msg);

        asprintf(&msg, "actual items list should not have an unmatched item at index [%d]", i);
        ASSERT_NE(actualItemHasMatch[i], -1) << msg;
        free(msg);
    }
}