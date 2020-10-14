#include <Arduino.h>

typedef const byte pin;
pin ROJO = 12;
pin AMBAR = 11;
pin VERDE = 10;

void setup() {
  pinMode(ROJO, OUTPUT);
  pinMode(AMBAR, OUTPUT);
  pinMode(VERDE, OUTPUT);

}

void loop() {
  digitalWrite(ROJO, HIGH);
  delay(2000);
  digitalWrite(ROJO, LOW);

  digitalWrite(VERDE, HIGH);
  delay(2000);
  digitalWrite(VERDE, LOW);

  
  digitalWrite(AMBAR, HIGH);
  delay(1000);
  digitalWrite(AMBAR, LOW);
}
