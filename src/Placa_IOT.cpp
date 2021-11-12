#include "Placa_IOT.h"

Placa_IOT::Placa_IOT()
{
    mcp.begin_I2C(0x20);
    Wire.setClock(1700000);
    mcp.pinMode(RELE1, OUTPUT);
    mcp.pinMode(RELE2, OUTPUT);
    mcp.pinMode(RELE3, OUTPUT);
    pinMode(pinData, OUTPUT);
    pinMode(pinClock, OUTPUT);
    pinMode(pinLatch, OUTPUT);
}

//LIGADO, DESLIGADO ou ALTERNAR
bool Placa_IOT::rele(uint8_t rele, uint8_t opcao)
{
    bool status;
    if (opcao == DESLIGADO)
    {
        mcp.digitalWrite(rele, LOW);
        status = LOW;
    }

    else if (opcao == LIGADO)
    {
        mcp.digitalWrite(rele, HIGH);
        status = HIGH;
    }

    else if (opcao == ALTERNAR)
    {
        status = !mcp.digitalRead(rele);
        mcp.digitalWrite(rele, status);
    }
    return status;
}

//Retorna o estado do rele
bool Placa_IOT::rele(uint8_t rele)
{
    bool status = !mcp.digitalRead(rele);
    return status;
}

void Placa_IOT::display(int numero)
{
    uint16_t valor[4];
    valor[0] = numero / 1000;
    valor[1] = (numero / 100) % 10;
    valor[2] = (numero / 10) % 10;
    valor[3] = numero % 10;

    digitalWrite(pinLatch, LOW);
    shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]]);
    shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
    digitalWrite(pinLatch, HIGH);

    (caractere_display < 3) ? caractere_display++ : caractere_display = 0;
}

void Placa_IOT::display(int numero, uint8_t dp)
{
    uint16_t valor[4];

    valor[0] = numero / 1000;
    valor[1] = (numero / 100) % 10;
    valor[2] = (numero / 10) % 10;
    valor[3] = numero % 10;

    if (caractere_display + 1 == display_dp)
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]] | 0b10000000);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    else
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]]);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    (caractere_display < 3) ? caractere_display++ : caractere_display = 0;
}

void Placa_IOT::display(char dA, int numero, uint8_t dp = 0)
{
    uint16_t valor[4];

    if (dA >= 'A' && dA <= 'F')
        valor[0] = dA - 55;
    else if (dA >= 'a' && dA <= 'f')
        valor[0] = dA - 87;
    else if (dA < 10)
        valor[0] = (int)dA;
    else
        valor[0] = 16;

    valor[1] = numero / 100;
    valor[2] = (numero / 10) % 10;
    valor[3] = numero % 10;

    if (caractere_display + 1 == display_dp)
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]] | 0b10000000);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    else
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]]);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    (caractere_display < 3) ? caractere_display++ : caractere_display = 0;
}

void Placa_IOT::display(char dA, char dB, int numero, uint8_t dp = 0)
{
    uint16_t valor[4];

    if (dA >= 'A' && dA <= 'F')
        valor[0] = dA - 55;
    else if (dA >= 'a' && dA <= 'f')
        valor[0] = dA - 87;
    else if (dA < 10)
        valor[0] = (int)dA;
    else
        valor[0] = 16;

    if (dB >= 'A' && dB <= 'F')
        valor[1] = dB - 55;
    else if (dB >= 'a' && dB <= 'f')
        valor[1] = dB - 87;
    else if (dB < 10)
        valor[1] = (int)dB;
    else
        valor[1] = 16;

    valor[2] = numero / 10;
    valor[3] = numero % 10;

    if (caractere_display + 1 == display_dp)
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]] | 0b10000000);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    else
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]]);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    (caractere_display < 3) ? caractere_display++ : caractere_display = 0;
}
void Placa_IOT::display(char dA, char dB, char dC, int numero, uint8_t dp = 0)
{
    uint16_t valor[4];

    if (dA >= 'A' && dA <= 'F')
        valor[0] = dA - 55;
    else if (dA >= 'a' && dA <= 'f')
        valor[0] = dA - 87;
    else if (dA < 10)
        valor[0] = (int)dA;
    else
        valor[0] = 16;

    if (dB >= 'A' && dB <= 'F')
        valor[1] = dB - 55;
    else if (dB >= 'a' && dB <= 'f')
        valor[1] = dB - 87;
    else if (dB < 10)
        valor[1] = (int)dB;
    else
        valor[1] = 16;

    if (dC >= 'A' && dC <= 'F')
        valor[2] = dC - 55;
    else if (dC >= 'a' && dC <= 'f')
        valor[2] = dC - 87;
    else if (dC < 10)
        valor[2] = (int)dC;
    else
        valor[2] = 16;

    valor[3] = numero % 10;

    if (caractere_display + 1 == display_dp)
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]] | 0b10000000);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    else
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]]);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    (caractere_display < 3) ? caractere_display++ : caractere_display = 0;
}
void Placa_IOT::display(char dA, char dB, char dC, char dD, uint8_t dp = 0)
{
    uint16_t valor[4];

    if (dA >= 'A' && dA <= 'F')
        valor[0] = dA - 55;
    else if (dA >= 'a' && dA <= 'f')
        valor[0] = dA - 87;
    else if (dA < 10)
        valor[0] = (int)dA;
    else
        valor[0] = 16;

    if (dB >= 'A' && dB <= 'F')
        valor[1] = dB - 55;
    else if (dB >= 'a' && dB <= 'f')
        valor[1] = dB - 87;
    else if (dB < 10)
        valor[1] = (int)dB;
    else
        valor[1] = 16;

    if (dC >= 'A' && dC <= 'F')
        valor[2] = dC - 55;
    else if (dC >= 'a' && dC <= 'f')
        valor[2] = dC - 87;
    else if (dC < 10)
        valor[2] = (int)dC;
    else
        valor[2] = 16;

    if (dD >= 'A' && dD <= 'F')
        valor[3] = dD - 55;
    else if (dD >= 'a' && dD <= 'f')
        valor[3] = dD - 87;
    else if (dD < 10)
        valor[3] = (int)dD;
    else
        valor[3] = 16;

    if (caractere_display + 1 == display_dp)
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]] | 0b10000000);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    else
    {
        digitalWrite(pinLatch, LOW);
        shiftOut(pinData, pinClock, MSBFIRST, mapaCaracteres7seg[valor[caractere_display]]);
        shiftOut(pinData, pinClock, MSBFIRST, seletorDisplay[caractere_display]);
        digitalWrite(pinLatch, HIGH);
    }

    (caractere_display < 3) ? caractere_display++ : caractere_display = 0;
}
