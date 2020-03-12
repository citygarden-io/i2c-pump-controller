#pragma once

#define I2C_ADDRESS 0x15
#define I2C_MAX_WRITE_BODY_SIZE 0x01
#define I2C_MAX_READ_BODY_SIZE 0x01
#define I2C_REGISTER_STATUS 0x01
#define I2C_REGISTER_PUMP_N_DESIRED_FLOW 0x10 // Internal use
#define I2C_REGISTER_PUMP_1_DESIRED_FLOW 0x11
#define I2C_REGISTER_PUMP_2_DESIRED_FLOW 0x12
#define I2C_REGISTER_PUMP_3_DESIRED_FLOW 0x13
#define I2C_REGISTER_PUMP_4_DESIRED_FLOW 0x14
#define I2C_REGISTER_PUMP_5_DESIRED_FLOW 0x15
#define I2C_REGISTER_PUMP_6_DESIRED_FLOW 0x16
#define I2C_REGISTER_PUMP_N_CURRENT_FLOW 0x20 // Internal use
#define I2C_REGISTER_PUMP_1_CURRENT_FLOW 0x21
#define I2C_REGISTER_PUMP_2_CURRENT_FLOW 0x22
#define I2C_REGISTER_PUMP_3_CURRENT_FLOW 0x23
#define I2C_REGISTER_PUMP_4_CURRENT_FLOW 0x24
#define I2C_REGISTER_PUMP_5_CURRENT_FLOW 0x25
#define I2C_REGISTER_PUMP_6_CURRENT_FLOW 0x26

class SlaveProtocol
{

public:
    SlaveProtocol();

    void setup();
    void loop();

    void processWireRequest();
    void processWireReceive(int bytesCount);

    void setCurrentFlowRate(char pumpNumber, char flowRate);
    char getDesiredFlowRate(char pumpNumber);

private:
    char desiredFlowRateRegistry[6] = {0};
    char currentFlowRateRegistry[6] = {0};

    char requestedRegister = 0;

    void handleCurrentFlowRead(char pumpNumber);
    void handleDesiredFlowRead(char pumpNumber);
    void handleDesiredFlowWrite(char pumpNumber, char flowRate);
    void handleStatusRead();
};

extern SlaveProtocol Protocol;