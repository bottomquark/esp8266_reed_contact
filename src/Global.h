/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <ArduinoLog.h>

/**
 * Helper method to print timestamp to Log output.
 */
void printTimestamp(Print *_logOutput)
{
    char c[12];
    sprintf(c, "%10lu ", millis());
    _logOutput->print(c);
}

/**
 * Helper method to print carriage return to Log output.
 */
void printNewline(Print *_logOutput)
{
    _logOutput->print(CR);
}

void setupLogger()
{
    // Initialize logger.
    Log.init(LOG_LEVEL_VERBOSE, 115200);
    Log.setPrefix(printTimestamp);
    Log.setSuffix(printNewline);
    Log.trace("--- start set-up ---");
}

#endif