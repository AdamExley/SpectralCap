#include "StatusLED.h"



StatusLED::StatusLED()
{
    pixel = new Adafruit_DotStar(1, 41, 40, DOTSTAR_RGB);
    pixel->begin();
    pixel->show();

    Green();
}


void StatusLED::ShowOn()
{
    pixel->show();
    isOn = true;
}


void StatusLED::Off()
{
    pixel->clear();
    pixel->show();
    isOn = false;
}

void StatusLED::Red()
{
    pixel->setPixelColor(0, 100, 0, 0);
    ShowOn();
}

void StatusLED::Green()
{
    pixel->setPixelColor(0, 0, 100, 0);
    ShowOn();
}

void StatusLED::Blue()
{
    pixel->setPixelColor(0, 0, 0, 100);
    ShowOn();
}

void StatusLED::Orange()
{
    pixel->setPixelColor(0, 255, 165, 0);
    ShowOn();
}

void StatusLED::Purple()
{
    pixel->setPixelColor(0, 152, 65, 158);
    ShowOn();
}