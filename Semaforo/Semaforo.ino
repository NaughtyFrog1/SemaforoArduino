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
    byte getSemaforos();
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

byte Semaforo::getSemaforos()
{
  return num_semaforos;
}



//* ===========================================================================
//* TESTS
//* ===========================================================================


//· TestConexiones ----------------------------------------------------------->

class TestConexiones
{
  private:
    Semaforo sem1, sem2, sem3, sem4;
  public:
    void begin();
    void testAll();
};

void TestConexiones::begin()
{
  sem1.begin(14, 15, 16);
  sem2.begin(17, 18, 19);
  sem3.begin(12, 11, 10);
  sem4.begin(9, 8, 7);
}

void TestConexiones::testAll()
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



//* ===========================================================================
//* PROGRAMA ARDUINO
//* ===========================================================================


TestConexiones prueba;

void setup()
{
  prueba.begin();
}

void loop()
{
  prueba.testAll();
}