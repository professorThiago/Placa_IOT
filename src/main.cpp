#include <Arduino.h>
#include "Placa_IOT.h"

Placa_IOT placa;

void setup() {
  placa.rele1_acionar();
  placa.rele1_desacionar();
}

void loop() {
  
}