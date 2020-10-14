#include <Arduino.h>
#include "Semaforo.ino"


Semaforo sem1, sem2, sem3, sem4;

void setup()
{
  sem1.begin(14, 15, 16);
  sem2.begin(18, 19, 20);
  sem3.begin(12, 11, 10);
  sem4.begin(7, 6, 5);
}

void loop()
{
  sem1.allOn();
  delay(1000);
  sem1.allOff();

  sem2.allOn();
  delay(1000);
  sem2.allOff();

  sem3.allOn();
  delay(1000);
  sem3.allOff();

  sem4.allOn();
  delay(1000);
  sem4.allOff();
}