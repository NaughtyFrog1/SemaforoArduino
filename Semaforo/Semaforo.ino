#include <Arduino.h>



//* ===========================================================================
//* DECLARACIÓN DE CLASES
//* ===========================================================================


//· Timer -------------------------------------------------------------------->

class Timer
{
private:
  int base_time;
  int steps;
public:
  Timer(int time);
  void Step();
};

Timer::Timer(int time)
{
  base_time = time;
}

void Timer::Step()
{
  ++steps;
  delay(base_time);
}


//· LuzSemaforo -------------------------------------------------------------->

class LuzSemaforo {
  private:
    byte pin;
  public:
    void begin(byte pin);
    void on();
    void off();
};

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

class Semaforo {
  private:
    static byte num_semaforos;  // Cuenta de la cantidad de semaforos
  public:
    LuzSemaforo rojo, ambar, verde;
    void begin(byte r, byte a, byte v);
    void allOn();
    void allOff();
};

void Semaforo::begin(byte r, byte a, byte v)
{
  rojo.begin(r);
  ambar.begin(a);
  verde.begin(v);
}

void Semaforo::allOn()
{
  rojo.on();
  ambar.on();
  verde.on();
}

void Semaforo::allOff()
{
  rojo.off();
  ambar.off();
  verde.off();
}



//* ===========================================================================
//* PROGRAMA ARDUINO
//* ===========================================================================


void setup()
{
}

void loop()
{

}