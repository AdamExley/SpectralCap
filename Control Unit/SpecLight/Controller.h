#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SerialCom.h"
#include "Arduino.h"
#include "Constants.h"

class Controller
{

    private:
        double ShutterTime = 1.0;
        double PrefocusTime = 0.5;
        double FocusTime = 0.5;
        double AfterTime = 0.25;
        double OverlapTime = 0.1;

        bool LightState[MAX_LED_NUM] = {0};

        int Sequence[MAX_SEQUENCE_LEN] = {0};


        void AllOff();
        void LEDState(int led_id, bool state);

        void ClearSequence();

        void SetFocus();
        void SetShutter();

        void StopShutter();

    public:
        void ExecuteCommand(Command command, lilParser& parser);


        void Capture(int led_id);
        void CaptureSequence();

        void SetShutterTime(double time);
        void SetPrefocusTime(double time);
        void SetFocusTime(double time);
        void SetAfterTime(double time);
        void SetOverlapTime(double time);

        void Dark();
        void Light(int led_id);

};



#endif