#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SerialCom.h"
#include "Arduino.h"
#include "Constants.h"
#include "StatusLED.h"

class Controller
{

    private:
        double ShutterTime = 1.0;
        double PrefocusTime = 2.0;
        double FocusTime = 1.0;
        double AfterTime = 0.1;
        double OverlapTime = 0.1;

        bool LightState[MAX_LED_NUM] = {};

        int Sequence[MAX_SEQUENCE_LEN] = {};

        StatusLED statusled;


        void AllOff();
        void LEDState(int led_id, bool state);

        void ClearSequence();

        void SetFocus();
        void SetShutter();

        void StopShutter();

        void SetSequence(lilParser& parser);

        void Focus(int led_id);

        void Capture(int led_id);
        void CaptureSequence();

        void SetShutterTime(double time);
        void SetPrefocusTime(double time);
        void SetFocusTime(double time);
        void SetAfterTime(double time);
        void SetOverlapTime(double time);

    public:
        void ExecuteCommand(Command command, lilParser& parser);

        void Dark();
        void Light(int led_id);

};



#endif