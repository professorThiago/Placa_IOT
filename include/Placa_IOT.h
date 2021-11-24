#ifndef PLACA_IOT_H
#define PLACA_IOT_H

#define RELE1 15
#define RELE2 14
#define RELE3 13
#define LIGADO 0x01
#define DESLIGADO 0x00
#define ALTERNAR 0x02
#define BOTAO1 16
#define BOTAO2 2
#define BOTAO3 0
#define DirMotorPasso 8 //! ???????
#define PINPASSO 9 //! ??????????
#define MS1 12
#define MS2 11
#define MS3 10 

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

class Placa_IOT
{
private:
    Adafruit_MCP23X17 mcp;
    const uint8_t mapaCaracteres7seg[17] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113, 64};
    const uint8_t seletorDisplay[4] = {254, 253, 251, 247};
    const uint8_t mapaCaracteresTeclado[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};
    const int mapaPinColuna[4] = {4, 5, 6, 7};
    const int mapaPinLinha[4] = {3, 2, 1, 0};
    const uint8_t pinData = 13;
    const uint8_t pinClock = 14;
    const uint8_t pinLatch = 12;
    uint8_t display_dp;
    uint8_t caractere_display;
    unsigned long tempoInicialBotao[3];
    bool estadoAnteriorBotao[3] = {0, 1, 1};
    const unsigned long tempoDebouce = 20;
    bool acaoExecutadaBotao[3] = {0, 1, 1};
    char teclaAnterior;
    unsigned long tempoUltimaLeituraTeclado;
    String password = "";
    String senha = "";
    unsigned long tempoEntreLeiturasTeclado = 100;
    int tarefaPasso=0;
    bool tarefaPassoExecutando = 0;
    unsigned long _tempoEntrePassos = 5;
    unsigned long tempoInicialPassos = 0;
    void passo();

public:
    Placa_IOT();
    bool rele(uint8_t rele);
    bool rele(uint8_t rele, uint8_t opcao);
    void display(int numero);
    void display(String numero);
    void display(int numero, uint8_t dp);
    void display(char dA, int numero, uint8_t dp);
    void display(char dA, char dB, int numero, uint8_t dp);
    void display(char dA, char dB, char dC, int numero, uint8_t dp);
    void display(char dA, char dB, char dC, char dD, uint8_t dp);
    bool botaoApertado(uint8_t botao, bool borda);
    char teclado();
    void formarPalavraSenha(char caractere);
    void definirSenha(String senha);
    void limparPalavraSenha();
    bool verificarSenha();
    String getSenha();
    void motorpasso(int passo);
    bool motorpassoUPDATE();
    void tempoEntrePassos(unsigned long tempo);
    void modoPasso(uint8_t);
};

#endif