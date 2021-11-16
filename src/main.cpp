#include <Arduino.h>
#include "Placa_IOT.h"

Placa_IOT placa;

void setup()
{
    Serial.begin(9600);
    placa.definirSenha("123");
}

void loop()
{
    char tecla = placa.teclado();
    if (tecla != 'n' && tecla != '#')
        placa.formarTentativaSenha(tecla);

    if (tecla == '#')
    {
        if (placa.verificarSenha())
            placa.rele(1, ALTERNAR);

            else
            Serial.println("SENHA ERRADA");

            placa.limparTentativaSenha();
    }
    placa.display(placa.getSenha());
}

