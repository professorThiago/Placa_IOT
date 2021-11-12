#include <Arduino.h>
#include "Placa_IOT.h"

Placa_IOT placa;

void setup() {
Serial.begin(9600);
}

void loop() {
placa.display(1, 123, 0);

}