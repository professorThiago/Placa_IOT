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

    pinMode(BOTAO1, INPUT);
    pinMode(BOTAO2, INPUT_PULLUP);
    pinMode(BOTAO3, INPUT_PULLUP);

    for (int i = 0; i < 4; i++)
    {
        mcp.pinMode(mapaPinLinha[i], OUTPUT);
        mcp.pinMode(mapaPinColuna[i], INPUT_PULLUP);
        mcp.digitalWrite(mapaPinLinha[i], HIGH);
    }

    mcp.pinMode(DirMotorPasso, OUTPUT);
    mcp.pinMode(PINPASSO, OUTPUT);
    mcp.pinMode(MS1, OUTPUT);
}

//LIGADO, DESLIGADO ou ALTERNAR
bool Placa_IOT::rele(uint8_t rele, uint8_t opcao)
{
    bool _status = 0;
    uint8_t selecaoRele = rele;
    if (selecaoRele <= 3)
    {
        if (selecaoRele == 1)
            selecaoRele = RELE1;
        else if (selecaoRele == 2)
            selecaoRele = RELE2;
        else if (selecaoRele == 3)
            selecaoRele = RELE3;
    }

    if (opcao == DESLIGADO)
    {
        mcp.digitalWrite(selecaoRele, LOW);
        _status = LOW;
    }

    else if (opcao == LIGADO)
    {
        mcp.digitalWrite(selecaoRele, HIGH);
        _status = HIGH;
    }

    else if (opcao == ALTERNAR)
    {
        _status = !mcp.digitalRead(selecaoRele);
        mcp.digitalWrite(selecaoRele, _status);
    }
    return _status;
}

//Retorna o estado do rele
bool Placa_IOT::rele(uint8_t rele)
{
    bool status = !mcp.digitalRead(rele);
    return status;
}

//
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

//
void Placa_IOT::display(String numero)
{
    display(numero.toInt());
}

//
void Placa_IOT::display(int numero, uint8_t dp)
{
    uint16_t valor[4];

    display_dp = dp;

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

//
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

    display_dp = dp;

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

//
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

    display_dp = dp;

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

//
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

    display_dp = dp;

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

//
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

    display_dp = dp;

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

//
bool Placa_IOT::botaoApertado(uint8_t botao, bool borda)
{
    bool statusSaida = 0;
    unsigned long tempoAtual = millis();

    uint8_t btn = botao - 1;
    if (btn > 2)
        btn = 0;

    uint8_t pinBotao;
    if (btn == 0)
        pinBotao = BOTAO1;
    else if (btn == 1)
        pinBotao = BOTAO2;
    else
        pinBotao = BOTAO3;

    bool estadoAtualBotao = digitalRead(pinBotao);

    if (estadoAtualBotao != estadoAnteriorBotao[btn])
        tempoInicialBotao[btn] = tempoAtual;

    if (tempoAtual - tempoInicialBotao[btn] > tempoDebouce)
    {
        if (acaoExecutadaBotao[btn] != estadoAtualBotao)
        {
            acaoExecutadaBotao[btn] = estadoAtualBotao;
            if (btn == 0)
            {
                if (estadoAtualBotao == borda)
                    statusSaida = 1;
            }

            else
            {
                if (estadoAtualBotao == !borda)
                    statusSaida = 1;
            }
        }
    }
    estadoAnteriorBotao[btn] = estadoAtualBotao;
    return statusSaida;
}

//
char Placa_IOT::teclado()
{
    char envio = 'n';
    unsigned long tempoAtual = millis();
    char teclaPressionada = 'n';
    if (tempoAtual - tempoUltimaLeituraTeclado > tempoEntreLeiturasTeclado)
    {
        tempoUltimaLeituraTeclado = tempoAtual;
        byte leitura = 0;

        for (int x = 0; x < 4; x++)
        {
            mcp.digitalWrite(mapaPinLinha[x], LOW);
            leitura = mcp.readGPIOA();
            leitura = leitura >> 4;
            for (int y = 0; y < 4; y++)
            {
                int bitLido = pow(2, y);
                if ((leitura & bitLido) == 0)
                    teclaPressionada = mapaCaracteresTeclado[x][y];
            }
            mcp.digitalWrite(mapaPinLinha[x], HIGH);
        }

        if (teclaPressionada != teclaAnterior)
        {
            envio = teclaPressionada;
            teclaAnterior = teclaPressionada;
        }
    }
    return envio;
}

//
void Placa_IOT::formarPalavraSenha(char caractere)
{
    password += caractere;
}

//
void Placa_IOT::definirSenha(String senha)
{
    this->senha = senha;
}

//
void Placa_IOT::limparPalavraSenha()
{
    password = "";
}

//
bool Placa_IOT::verificarSenha()
{
    return (senha == password) ? true : false;
}

//
String Placa_IOT::getSenha()
{
    return password;
}

//
void Placa_IOT::motorpasso(int passo)
{
    if (!tarefaPassoExecutando)
        tarefaPasso = passo;
}
//
bool Placa_IOT::motorpassoUPDATE()
{
    unsigned long tempoAtual = millis();
    if (tarefaPassoExecutando == 0 && tarefaPasso != 0)
    {
        if (tarefaPasso < 0)
        {
            tarefaPasso = abs(tarefaPasso);
            mcp.digitalWrite(DirMotorPasso, 0);
        }
        else
            mcp.digitalWrite(DirMotorPasso, 1);

        tarefaPassoExecutando = 1;
    }

    if (tarefaPassoExecutando)
    {
        if (tempoAtual - tempoInicialPassos > _tempoEntrePassos)
        {
            tempoInicialPassos = tempoAtual;

            if (tarefaPasso > 0)
            {
                passo();
                tarefaPasso--;

                if (tarefaPasso == 0)
                {
                    tarefaPassoExecutando = 0;
                }
            }
        }
    }
    return tarefaPassoExecutando;
}

void Placa_IOT::passo()
{
    mcp.digitalWrite(PINPASSO, HIGH);
    mcp.digitalWrite(PINPASSO, LOW);
}

void Placa_IOT::tempoEntrePassos(unsigned long tempo)
{
    _tempoEntrePassos = tempo;
}

void Placa_IOT::modoPasso(uint8_t MODO)
{
    switch (MODO)
    {
    case 2:
        mcp.digitalWrite(MS1, HIGH);
        mcp.digitalWrite(MS2, LOW);
        mcp.digitalWrite(MS3, LOW);
        break;

    case 4:
        mcp.digitalWrite(MS1, LOW);
        mcp.digitalWrite(MS2, HIGH);
        mcp.digitalWrite(MS3, LOW);
        break;

    case 8:
        mcp.digitalWrite(MS1, HIGH);
        mcp.digitalWrite(MS2, HIGH);
        mcp.digitalWrite(MS3, LOW);
        break;

    case 16:
        mcp.digitalWrite(MS1, HIGH);
        mcp.digitalWrite(MS2, HIGH);
        mcp.digitalWrite(MS3, HIGH);
        break;

    default:
        mcp.digitalWrite(MS1, LOW);
        mcp.digitalWrite(MS2, LOW);
        mcp.digitalWrite(MS3, LOW);
        break;
    }
}
