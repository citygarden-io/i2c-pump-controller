#include <Arduino.h>
#include <Wire.h>
#include "protocol.h"

SlaveProtocol::SlaveProtocol()
{
    char pumpNumber;

    for (pumpNumber = 1; pumpNumber <= 6; pumpNumber++)
    {
        this->currentFlowRateRegistry[pumpNumber - 1] = 0;
        this->desiredFlowRateRegistry[pumpNumber - 1] = 0;
    }
}

void SlaveProtocol::setup()
{
    Serial.println("[SlaveProtocol] Setup started.");
    Wire.begin(I2C_ADDRESS);

    Wire.onRequest([]() {
        Protocol.processWireRequest();
    });

    Wire.onReceive([](int bytesCount) {
        Protocol.processWireReceive(bytesCount);
    });

    Serial.println("[SlaveProtocol] Setup complete.");
}

void SlaveProtocol::loop()
{
}

void SlaveProtocol::setCurrentFlowRate(char pumpNumber, char flowRate)
{
}

char SlaveProtocol::getDesiredFlowRate(char pumpNumber)
{
    return 0;
}

void SlaveProtocol::processWireRequest()
{
    switch (this->requestedRegister)
    {
    case I2C_REGISTER_STATUS:
        Wire.write(0xFF);
        break;
    case I2C_REGISTER_PUMP_1_DESIRED_FLOW:
        break;
    case I2C_REGISTER_PUMP_2_DESIRED_FLOW:
        break;
    case I2C_REGISTER_PUMP_3_DESIRED_FLOW:
        break;
    case I2C_REGISTER_PUMP_4_DESIRED_FLOW:
        break;
    case I2C_REGISTER_PUMP_5_DESIRED_FLOW:
        break;
    case I2C_REGISTER_PUMP_6_DESIRED_FLOW:
        break;
    case I2C_REGISTER_PUMP_1_CURRENT_FLOW:
        break;
    case I2C_REGISTER_PUMP_2_CURRENT_FLOW:
        break;
    case I2C_REGISTER_PUMP_3_CURRENT_FLOW:
        break;
    case I2C_REGISTER_PUMP_4_CURRENT_FLOW:
        break;
    case I2C_REGISTER_PUMP_5_CURRENT_FLOW:
        break;
    case I2C_REGISTER_PUMP_6_CURRENT_FLOW:
        break;

    default:
        break;
    }

    this->requestedRegister = 0;
}

void SlaveProtocol::processWireReceive(int bytesCount)
{
    bool isRead = (bytesCount == 1);
    char registerValue;
    char logLine[80];

    this->requestedRegister = Wire.read();

    if (isRead)
    {
        sprintf(logLine, "[SlaveProtocol] Received read request from 0x%02X register.", this->requestedRegister);
        Serial.println(logLine);
        // Returning, rest of read processing goes to processWireRequest() method.
        return;
    }
    else
    {
        Wire.readBytes(&registerValue, 1);
        sprintf(logLine, "[SlaveProtocol] Received write 0x%02X value request to 0x%02X register.", registerValue, this->requestedRegister);
        Serial.println(logLine);
    }

    // Reading rest of garbage
    while (Wire.available() > 0)
    {
        Wire.read();
    }

    switch (this->requestedRegister)
    {
    case I2C_REGISTER_PUMP_1_DESIRED_FLOW:
        this->desiredFlowRateRegistry[0] = registerValue;
        break;
    case I2C_REGISTER_PUMP_2_DESIRED_FLOW:
        this->desiredFlowRateRegistry[1] = registerValue;
        break;
    case I2C_REGISTER_PUMP_3_DESIRED_FLOW:
        this->desiredFlowRateRegistry[2] = registerValue;
        break;
    case I2C_REGISTER_PUMP_4_DESIRED_FLOW:
        this->desiredFlowRateRegistry[3] = registerValue;
        break;
    case I2C_REGISTER_PUMP_5_DESIRED_FLOW:
        this->desiredFlowRateRegistry[4] = registerValue;
        break;
    case I2C_REGISTER_PUMP_6_DESIRED_FLOW:
        this->desiredFlowRateRegistry[5] = registerValue;
        break;
    default:
        break;
    }
}

SlaveProtocol Protocol = SlaveProtocol();