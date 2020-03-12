#include <Arduino.h>
#include <Wire.h>

#include "controller.h"
#include "protocol.h"

#define SERIAL_BAUDRATE 115200

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);

    Serial.println("[SYS] Hello :-)");

    Controller.setup();
    Protocol.setup();
}

void loop()
{
    Controller.loop();
    Protocol.loop();

    char pumpNumber;

    for (pumpNumber = 1; pumpNumber <= 6; pumpNumber++)
    {
        char desiredFlowRate = Protocol.getDesiredFlowRate(pumpNumber);
        Controller.setDesiredFlowRate(pumpNumber, desiredFlowRate);

        char currentFlowRate = Controller.getCurrentFlowRate(pumpNumber);
        Protocol.setCurrentFlowRate(pumpNumber, currentFlowRate);
    }
}
