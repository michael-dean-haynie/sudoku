#include "assertion-helpers.h"
#include <gtest/gtest.h>

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
