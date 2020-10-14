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
    //...
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

// ...



//* ===========================================================================
//* PROGRAMA ARDUINO
//* ===========================================================================

void setup()
{

}

void loop()
{

}