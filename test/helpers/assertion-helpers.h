#pragma once

extern "C" {
#include "progress-event.h"
}

/**
 * Helper that runs google test assertions to check the values of ProgressEvent members.
 * @param expected a pointer to the expected ProgressEvent
 * @param actual a pointer to the actual ProgressEvent
 */
void assertProgressEventsMatch(ProgressEvent *expected, ProgressEvent *actual);

/**
 * Helper that runs google test assertions to check the values of ProgressEventLists
 * @param expected a pointer to the expected ProgressEventList
 * @param actual a pointer to the actual ProgressEventList
 */
void assertProgressEventListsMatch(ProgressEventList *expected, ProgressEventList *actual);