#include "Placa_IOT.h"

Placa_IOT::Placa_IOT()
{
mcp.begin_I2C(0x20);
Wire.setClock(1700000);
mcp.pinMode(PINRELE1, OUTPUT);

}

void Placa_IOT::rele1_acionar()
{
    mcp.digitalWrite(PINRELE1, HIGH);
}

void Placa_IOT::rele1_desacionar()
{
    mcp.digitalWrite(PINRELE1, LOW);
}

bool Placa_IOT::rele1_alternar()
{
    bool status = !mcp.digitalRead(PINRELE1);
    mcp.digitalWrite(PINRELE1, status);
    return status;
}