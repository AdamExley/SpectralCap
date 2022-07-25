#include "SerialCom.h"


void DisplayHelp()
{
    Serial.println("Valid Commands:");
    Serial.println("_______________________________________________");
    Serial.println("shutter / shut - Set shutter time");
    Serial.println("prefocus / prefoc - Set prefocus light time");
    Serial.println("focus / foc - Focus time");
    Serial.println("after / aft - Set time after shutter");
    Serial.println("overlap / over - Set LED overlap time");
    Serial.println("sequence / seq - Set LED sequence");
    Serial.println("                 Index '0' is a blank frame");
    Serial.println("                 Last arg should be 'end'");
    Serial.println("-----------------------------------------------");
    Serial.println("capture_sequence / cap_seq - Full cap sequence");
    Serial.println("capture / cap - Capture with a single LED ");
    Serial.println("focus_now / foc_now - Focus with a single LED ");
    Serial.println("light - Turn on an LED");
    Serial.println("dark - turn off all LEDs");
}


void SetupCommands(lilParser& parser)
{
    parser.addCmd(SET_SHUTTER,"shutter");
    parser.addCmd(SET_SHUTTER,"shut");

    parser.addCmd(TIME_PREFOCUS,"prefocus");
    parser.addCmd(TIME_PREFOCUS,"prefoc");

    parser.addCmd(TIME_FOCUS,"focus");
    parser.addCmd(TIME_FOCUS,"foc");

    parser.addCmd(TIME_AFTER,"after");
    parser.addCmd(TIME_AFTER,"aft");

    parser.addCmd(TIME_OVERLAP,"overlap");
    parser.addCmd(TIME_OVERLAP,"over");

    parser.addCmd(SET_SEQUENCE,"sequence");
    parser.addCmd(SET_SEQUENCE,"seq");

    parser.addCmd(CAPTURE,"capture");
    parser.addCmd(CAPTURE,"cap");

    parser.addCmd(CAPTURE_SEQUENCE,"capture_sequence");
    parser.addCmd(CAPTURE_SEQUENCE,"cap_seq");

    parser.addCmd(FOCUS,"focus_now");
    parser.addCmd(FOCUS,"foc_now");

    parser.addCmd(LIGHT,"light");
    parser.addCmd(DARK,"dark");

    parser.addCmd(HELP,"help");
    parser.addCmd(HELP,"h");
    
}
