#include "Controller.h"

#define DEBUG

void Controller::Capture(int led_id)
{
    statusled.Blue();
    // Other code here
    Light(led_id);
    #ifdef DEBUG
    Serial.println("DEBUG::Staring Capture with LED " + String(led_id));
    #endif

    SetFocus();

    delayMicroseconds((int) 1000000 * FocusTime);

    statusled.Off();

    SetShutter();

    delay(100);

    StopShutter();

    delayMicroseconds((int) 1000000 * ShutterTime);

    statusled.Purple();

    delayMicroseconds((int) 1000000 * AfterTime);

    #ifdef DEBUG
    Serial.println("DEBUG::Capture Complete");
    #endif
    statusled.Green();

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
    #ifdef DEBUG
    Serial.println("DEBUG::Sequence cleared");
    #endif
}


void Controller::CaptureSequence()
{
    statusled.Blue();
    // Find location of last light command
    int LastCommand = 0;
    for (size_t i = 0; i < MAX_SEQUENCE_LEN; i++)
        if (Sequence[i] != 0)   LastCommand = i;

    // Turn all LEDs off
    AllOff();

    // Extra delay
    delayMicroseconds((int) 1000000 * OverlapTime);
    LEDState(Sequence[0], HIGH);

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

        statusled.Off();

        SetShutter();

        delay(100);

        StopShutter();

        delayMicroseconds((int) 1000000 * ShutterTime);

        statusled.Blue();

        delayMicroseconds((int) 1000000 * AfterTime);
    }

    // Turn off last LED
    LEDState(Sequence[LastCommand], LOW);

    statusled.Green();
    
}

void Controller::LEDState(int led_id, bool state)
{
    // Assume led_id 0 corresponds to no LED
    if (led_id == 0)    return;

    digitalWrite(OutputPins[led_id - 1], state);
    LightState[led_id - 1] = state;
}

void Controller::AllOff()
{
    for(int i = 0; i < MAX_LED_NUM; i++)
        LEDState(i+1, LOW);
}


void Controller::SetShutterTime(double time)
{
    statusled.Orange();
    ShutterTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::ShutterTime: " + String(time));
    #endif
    statusled.Green();
}

void Controller::SetPrefocusTime(double time)
{
    statusled.Orange();
    PrefocusTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::PreFocusTime: " + String(time));
    #endif
    statusled.Green();
}

void Controller::SetFocusTime(double time)
{
    statusled.Orange();
    FocusTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::FocusTime: " + String(time));
    #endif
    statusled.Green();
}

void Controller::SetAfterTime(double time)
{
    statusled.Orange();
    AfterTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::AfterTime: " + String(time));
    #endif
    statusled.Green();
}

void Controller::SetOverlapTime(double time)
{
    statusled.Orange();
    OverlapTime = time;
    #ifdef DEBUG
    Serial.println("DEBUG::OverlapTime: " + String(time));
    #endif
    statusled.Green();

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
    statusled.Orange();
    // Skip if already lit
    if (LightState[led_id]) return;

    AllOff();
    delay(50);
    LEDState(led_id, HIGH);
    #ifdef DEBUG
    Serial.println("DEBUG::LED " + String(led_id) + " lit");
    #endif
    statusled.Green();

}


void Controller::Focus(int led_id)
{
    statusled.Blue();
    
    Light(led_id);
    delay(50);
    SetFocus();
    delay((int)FocusTime * 1000);
    StopShutter();
    #ifdef DEBUG
    Serial.println("DEBUG::Focused using LED " + String(led_id));
    #endif
    statusled.Green();
}

void Controller::SetSequence(lilParser& parser)
{
    statusled.Orange();
    ClearSequence();

    int seq_len = parser.numParams();

    for (size_t i = 0; i < seq_len; i++)
    {
        Sequence[i] = atoi(parser.getParam());
    }
    #ifdef DEBUG
    Serial.print("DEBUG::Sequence Echo: ");
    Serial.print(Sequence[0])
    for (size_t i = 1; i < seq_len; i++)
    {
        Serial.print("-"+String(Sequence[i]));
    }
    Serial.println("DEBUG::Sequence Set");
    #endif
    statusled.Green();

}



void Controller::ExecuteCommand(Command command, lilParser& parser)
{
    statusled.Purple();
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
            case TIME_FOCUS:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::TIME_FOCUS command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            SetFocusTime(atof(parser.getParamBuff()));
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

        case SET_SEQUENCE:
            if (parser.numParams() == 0)
            {
                Serial.println("ERROR::SET_SEQUENCE requires at least one argument");
                break;
            } else if (parser.numParams() > MAX_SEQUENCE_LEN)
            {
                Serial.println("ERROR::SET_SEQUENCE has maximum length of " + String(MAX_SEQUENCE_LEN) + ". But " + String(parser.numParams()) + " args given.");
                break;
            }
            SetSequence(parser);
            break; 



        case CAPTURE_SEQUENCE:
            if (parser.numParams() > 0)
            {
                Serial.println("WARN::CAPTURE_SEQUENCE expects no args. " + String(parser.numParams()) + " given. Ignoring.");
                break;
            }
            CaptureSequence();
            break; 

        case CAPTURE:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::CAPTURE command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            Capture(atoi(parser.getParamBuff()));
            break; 

        case FOCUS:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::FOCUS command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            Focus(atoi(parser.getParamBuff()));
            break;   

        case LIGHT:
            if (parser.numParams() != 1)
            {
                Serial.println("ERROR::LIGHT command expects 1 arg. " + String(parser.numParams()) + " given.");
                break;
            }
            Light(atoi(parser.getParamBuff()));
            break;   

        case DARK:
            if (parser.numParams() > 0)
            {
                Serial.println("WARN::DARK expects no args. " + String(parser.numParams()) + " given. Ignoring.");
                break;
            }
            Dark();
            break;    
               
            

        default:  break;
    }

    statusled.Green();
}