#include <Arduino.h>
#include "controller.h"
#include "specification.h"

void PumpController::setup()
{
    Serial.println("[PumpController] Setup started.");

    pinMode(PIN_PWM_OUT_1, OUTPUT);
    pinMode(PIN_PWM_OUT_2, OUTPUT);
    pinMode(PIN_PWM_OUT_3, OUTPUT);
    pinMode(PIN_PWM_OUT_4, OUTPUT);
    pinMode(PIN_PWM_OUT_5, OUTPUT);
    pinMode(PIN_PWM_OUT_6, OUTPUT);

    pinMode(PIN_TICK_IN_1, INPUT);
    pinMode(PIN_TICK_IN_2, INPUT);
    pinMode(PIN_TICK_IN_3, INPUT);
    pinMode(PIN_TICK_IN_4, INPUT);
    pinMode(PIN_TICK_IN_5, INPUT);
    pinMode(PIN_TICK_IN_6, INPUT);

    Serial.println("[PumpController] Setup complete.");
}

void PumpController::loop()
{
    char pumpNumber;

    for (pumpNumber = 1; pumpNumber <= PUMP_OUTPUT_COUNT; pumpNumber++)
    {
        analogWrite(this->getPWMPin(pumpNumber), this->desiredFlowRate[pumpNumber - 1]);
    }
}

void PumpController::setDesiredFlowRate(char pumpNumber, char flowRate)
{
    char logLine[64];
    if (pumpNumber > PUMP_OUTPUT_COUNT)
    {
        return;
    }

    if (this->desiredFlowRate[pumpNumber - 1] == flowRate)
    {
        return;
    }

    this->desiredFlowRate[pumpNumber - 1] = flowRate;

    sprintf(logLine, "[PumpController] Setting desired flow rate on pump #%d to %d.", pumpNumber, flowRate);
    Serial.println(logLine);
}

char PumpController::getCurrentFlowRate(char pumpNumber)
{
    if (pumpNumber > PUMP_OUTPUT_COUNT)
    {
        return 0;
    }

    return this->currentFlowRate[pumpNumber - 1];
}

char PumpController::getPWMPin(char pumpNumber)
{
    switch (pumpNumber)
    {
    case 1:
        return PIN_PWM_OUT_1;
    case 2:
        return PIN_PWM_OUT_2;
    case 3:
        return PIN_PWM_OUT_3;
    case 4:
        return PIN_PWM_OUT_4;
    case 5:
        return PIN_PWM_OUT_5;
    case 6:
        return PIN_PWM_OUT_6;

    default:
        return 0;
    }
}

char PumpController::getTickPin(char pumpNumber)
{
    switch (pumpNumber)
    {
    case 1:
        return PIN_TICK_IN_1;
    case 2:
        return PIN_TICK_IN_2;
    case 3:
        return PIN_TICK_IN_3;
    case 4:
        return PIN_TICK_IN_4;
    case 5:
        return PIN_TICK_IN_5;
    case 6:
        return PIN_TICK_IN_6;

    default:
        return 0;
    }
}

PumpController Controller = PumpController();