#ifndef SERIALCOM_H
#define SERIALCOM_H

#include "lilParser.h"


enum Command
{
    NONE,
    HELP,
    SET_SHUTTER,  
    TIME_PREFOCUS, 
    TIME_FOCUS,     
    TIME_AFTER,     
    TIME_OVERLAP,
    SET_SEQUENCE, ///
    CAPTURE,  
    CAPTURE_SEQUENCE, ///
    FOCUS,
    LIGHT,
    DARK
};


void DisplayHelp();
void SetupCommands(lilParser& parser);









#endif
