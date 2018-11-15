/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _INIT_H_
#define _INIT_H_

#include <ArduinoLog.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_VERBOSE
#endif

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
    Log.init(LOG_LEVEL, 115200);
    Log.setPrefix(printTimestamp);
    Log.setSuffix(printNewline);
    Log.trace("--- start set-up ---");
}

#endif