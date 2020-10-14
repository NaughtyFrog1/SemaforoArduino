#include <Arduino.h>


class LuzSemaforo {
  private:
    byte pin;
  public:
    void begin(byte pin);
};

class Semaforo {
  private:
    // ...
  public:
    //...
};


void LuzSemaforo::begin(byte pin_luz)
{
  pin = pin_luz;
  pinMode(pin, OUTPUT);
}

void setup()
{

}

void loop()
{

}