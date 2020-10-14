#include <Arduino.h>


//* ===========================================================================
//* DECLARACIÓN DE CLASES
//* ===========================================================================

class LuzSemaforo {
  private:
    byte pin;
  public:
    void begin(byte pin);
    void on();
    void off();
};

class Semaforo {
  private:
    // ...
  public:
    LuzSemaforo rojo, ambar, verde;
    void begin(byte r, byte a, byte v);
};



//* ===========================================================================
//* DEFINICIÓN DE MÉTODOS
//* ===========================================================================


//· LuzSemaforo -------------------------------------------------------------->

void LuzSemaforo::begin(byte pin_luz)
{
  pin = pin_luz;
  pinMode(pin, OUTPUT);
}

void LuzSemaforo::on()
{
  digitalWrite(pin, HIGH);
}

void LuzSemaforo::off()
{
  digitalWrite(pin, LOW);
}


//· Semaforo ----------------------------------------------------------------->

void Semaforo::begin(byte r, byte a, byte v)
{
  rojo.begin(r);
  ambar.begin(a);
  verde.begin(v);
}



//* ===========================================================================
//* PROGRAMA ARDUINO
//* ===========================================================================

Semaforo sem1;

void setup()
{
  sem1.begin(12, 11, 10);
}

void loop()
{
  sem1.verde.on();
}