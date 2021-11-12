#ifndef PLACA_IOT_H
#define PLACA_IOT_H

#define PINRELE1 15

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>


class Placa_IOT
{
    private:
    Adafruit_MCP23X17 mcp;
    



    public:
    Placa_IOT();
    void rele1_acionar();
    void rele1_desacionar();
    bool rele1_alternar();
    


};

#endif