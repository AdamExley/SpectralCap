#ifndef SERIALCOM_H
#define SERIALCOM_H

#include "lilParser.h"


enum Command
{
    NONE,
    HELP,
    SET_SHUTTER,    // Set shutter speed. Single arg
    TIME_PREFOCUS,  // Set prefoc time. Single arg
    TIME_FOCUS,     // Set focus time. Single arg
    TIME_AFTER,     // Set after time. Single arg
    TIME_OVERLAP,
    SET_SEQUENCE,   // Set a sequence of colors to use. 2-N args
    CAPTURE,        // Capture with a single color. Takes color # as arg
    CAPTURE_SEQUENCE,    // Capture the set sequence
    FOCUS,
    LIGHT,
    DARK
};


void DisplayHelp();
void SetupCommands(lilParser& parser);









#endif
