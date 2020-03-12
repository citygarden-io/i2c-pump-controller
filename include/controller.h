#pragma once

#define PIN_PWM_OUT_1 3
#define PIN_PWM_OUT_2 5
#define PIN_PWM_OUT_3 6
#define PIN_PWM_OUT_4 9
#define PIN_PWM_OUT_5 10
#define PIN_PWM_OUT_6 11

#define PIN_TICK_IN_1 2
#define PIN_TICK_IN_2 4
#define PIN_TICK_IN_3 7
#define PIN_TICK_IN_4 8
#define PIN_TICK_IN_5 14
#define PIN_TICK_IN_6 15

class PumpController
{
public:
    void setup();
    void loop();

    void setDesiredFlowRate(char pumpNumber, char flowRate);
    char getCurrentFlowRate(char pumpNumber);

private:
    char desiredFlowRate[6] = {0};
    char currentFlowRate[6] = {0};

    char getPWMPin(char pumpNumber);
    char getTickPin(char pumpNumber);
};

extern PumpController Controller;