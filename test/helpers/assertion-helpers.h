#pragma once

#include "progress-event.h"

/**
 * Helper that runs google test assertions to check the values of ProgressEvent members.
 * @param expected a pointer to the expected ProgressEvent
 * @param actual a pointer to the actual ProgressEvent
 */
void assertProgressEventsMatch(ProgressEvent *expected, ProgressEvent *actual);