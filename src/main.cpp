#include <Arduino.h>
#include "Placa_IOT.h"

Placa_IOT placa;

void setup()
{

    placa.tempoEntrePassos(1); //tempo em mSegundos entre os passos
    placa.modoPasso(1); //modo full step
    placa.motorpasso(200); //quantidade de passos a serem dados
}

void loop()
{
   //função necessária para movimentar o motor, retorna zero quando
   // o motor estiver parado
   bool motorRodadando = placa.motorpassoUPDATE(); 
   if(motorRodadando)
   {
       Serial.println("motor em movimento");
   }
}
