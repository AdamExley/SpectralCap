
#include "Controller.h"
#include "Constants.h"


Controller control;
lilParser CommandParser;


void setup() {
    // put your setup code here, to run once:

    pinMode(JACK_FOCUS, OUTPUT);
    pinMode(JACK_SHUTT, OUTPUT);

    for(int i = 0; i < MAX_LED_NUM; i++)
    {
        pinMode(OutputPins[i], OUTPUT);
        digitalWrite(OutputPins[i], LOW);
    }

    Serial.begin(BAUDRATE);

    SetupCommands(CommandParser);


}

void loop() {
    // put your main code here, to run repeatedly:
    char  inChar;
    Command   command;

    if (Serial.available()) {                                   // If serial has some data..
        inChar = Serial.read();                                  // Read out a charactor.
        command = (Command)CommandParser.addChar(inChar);                     // Try parsing what we have.
        control.ExecuteCommand(command, CommandParser);
    }


}
