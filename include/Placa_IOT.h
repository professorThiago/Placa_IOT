#ifndef PLACA_IOT_H
#define PLACA_IOT_H


#define RELE1 15
#define RELE2 14
#define RELE3 13
#define LIGADO 0x01
#define DESLIGADO 0x00
#define ALTERNAR 0x02



#include <Arduino.h>
#include <Adafruit_MCP23X17.h>


class Placa_IOT
{
    private:
    Adafruit_MCP23X17 mcp;
    const uint8_t mapaCaracteres7seg[17] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113, 64};
    const uint8_t seletorDisplay[4] = {254, 253, 251, 247};
    const uint8_t pinData = 13;
    const uint8_t pinClock = 14;
    const uint8_t pinLatch = 12;
    uint8_t display_dp;
    uint8_t caractere_display;


    public:
    Placa_IOT();
    bool rele(uint8_t rele);
    bool rele(uint8_t rele, uint8_t opcao);
    void display(int numero);
    void display(int numero, uint8_t dp);
    void display(char dA, int numero, uint8_t dp);
    void display(char dA, char dB, int numero, uint8_t dp);
    void display(char dA, char dB, char dC, int numero, uint8_t dp);
    void display(char dA, char dB, char dC, char dD, uint8_t dp);
    bool botao(uint8_t botao);
    bool botao(uint8_t botao, int mS_Apertado);


};

#endif