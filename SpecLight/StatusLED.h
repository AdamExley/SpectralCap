#ifndef STATUS_LED_H
#define STATUS_LED_H

#include "Arduino.h"
#include "Adafruit_DotStar.h"

class StatusLED
{
    private:
        Adafruit_DotStar *pixel;
        bool isOn = false;

        void ShowOn();
    public:
        StatusLED();
        void Off();
        void Red();
        void Green();
        void Blue();
        void Orange();
        void Purple();
};


#endif