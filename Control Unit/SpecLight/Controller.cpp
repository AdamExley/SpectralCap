#include "Controller.h"

#define DEBUG

void Controller::Capture(int led_id)
{
    // Other code here
}

void Controller::SetFocus()
{
    digitalWrite(JACK_FOCUS, HIGH);
}

void Controller::SetShutter()
{
    digitalWrite(JACK_SHUTT, HIGH);
}

void Controller::StopShutter()
{
    digitalWrite(JACK_SHUTT, LOW);
    digitalWrite(JACK_FOCUS, LOW);
}

void Controller::ClearSequence()
{
    for(int i = 0; i < MAX_SEQUENCE_LEN; i++)
        Sequence[i] = 0;
}


void Controller::CaptureSequence()
{
    // Find location of last light command
    int LastCommand = 0;
    for (size_t i = 0; i < MAX_SEQUENCE_LEN; i++)
        if (Sequence[i] != 0)   LastCommand = i;

    // Turn all LEDs off
    AllOff();

    // Extra delay
    delayMicroseconds((int) 1000000 * OverlapTime);

    // Go through the rest of the commands
    for (size_t i = 0; i < LastCommand + 1; i++)
    {
        // Turn on LED
        LEDState(Sequence[i], HIGH);

        // Overlap Delay
        delayMicroseconds((int) 1000000 * OverlapTime);

        // Turn off last LED
        if (i != 0)
            LEDState(Sequence[i - 1], LOW);
        
        delayMicroseconds((int) 1000000 * PrefocusTime);

        SetFocus();

        delayMicroseconds((int) 1000000 * FocusTime);

        SetShutter();

        delay(100);

        StopShutter();

        delayMicroseconds((int) 1000000 * ShutterTime);

        delayMicroseconds((int) 1000000 * AfterTime);
    }

    // Turn off last LED
    LEDState(Sequence[LastCommand], LOW);
    
}

void Controller::LEDState(int led_id, bool state)
{
    // Assume led_id 0 corresponds to no LED
    if (led_id == 0)    return;

    digitalWrite(OutputPins[led_id - 1], state);
    LightState[led_id] = state;
}

void Controller::AllOff()
{
    for(int i = 0; i < MAX_LED_NUM; i++)
        LEDState(i+1, LOW);
}


void Controller::SetShutterTime(double time)
{
    ShutterTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::ShutterTime: " + String(time));
    #endif
}

void Controller::SetPrefocusTime(double time)
{
    PrefocusTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::PreFocusTime: " + String(time));
    #endif
}

void Controller::SetFocusTime(double time)
{
    FocusTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::FocusTime: " + String(time));
    #endif
}

void Controller::SetAfterTime(double time)
{
    AfterTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::AfterTime: " + String(time));
    #endif
}

void Controller::SetOverlapTime(double time)
{
    OverlapTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::OverlapTime: " + String(time));
    #endif
}

void Controller::Dark()
{
    AllOff();
    #ifdef DEBUG
    Serial.println("DEBUG::Dark");
    #endif
}


void Controller::Light(int led_id)
{
    // Skip if already lit
    if (LightState[led_id]) return;

    AllOff();
    delay(50);
    LEDState(led_id, HIGH);
}


void Controller::ExecuteCommand(Command command, lilParser& parser)
{
    switch (command)
    {
        case NONE: break;
        case HELP: DisplayHelp(); break;
        case SET_SHUTTER:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::SET_SHUTTER command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            SetShutterTime(atof(parser.getParamBuff()));
            break;
        case TIME_PREFOCUS:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::TIME_PREFOCUS command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            SetPrefocusTime(atof(parser.getParamBuff()));
            break;
        case TIME_AFTER:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::TIME_AFTER command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            SetAfterTime(atof(parser.getParamBuff()));
            break;        
        case TIME_OVERLAP:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::TIME_OVERLAP command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            SetOverlapTime(atof(parser.getParamBuff()));
            break;     



        case DARK:
            if (parser.numParams() > 0)
            {
                Serial.println("WARN::DARK expects no args. " + String(parser.numParams()) + " given.");
                break;
            }
            Dark();
            break;    
               
            

        default:  break;
    }





}