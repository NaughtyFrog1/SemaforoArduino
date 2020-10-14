#include <Arduino.h>



//* ===========================================================================
//* DECLARACIÓN DE CLASES
//* ===========================================================================


//· Timer -------------------------------------------------------------------->

class Timer
{
private:
  int base_time;
public:
  Timer();
  void SetBaseTime(int mult);
  void Stop(int x);
};

Timer::Timer()
{
  base_time = 1000;  // milisegundos a segundos
}

void Timer::SetBaseTime(int mult)
{
  base_time = mult * 1000;
}

void Timer::Stop(int time)
{
  delay(time * base_time);
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
    Timer t;
    Semaforo sem1, sem2, sem3, sem4;
  public:
    void begin(byte r1, byte a1, byte v1, 
               byte r2, byte a2, byte v2,
               byte r3, byte a3, byte v3,
               byte r4, byte a4, byte v4);
    void testAll();
};

void TestConexiones::begin(byte r1, byte a1, byte v1, 
                           byte r2, byte a2, byte v2,
                           byte r3, byte a3, byte v3,
                           byte r4, byte a4, byte v4)
{
  sem1.begin(r1, a1, v1);
  sem2.begin(r2, a2, v2);
  sem3.begin(r3, a3, v3);
  sem4.begin(r4, a4, v4);
}

void TestConexiones::testAll()
{
  for (int i = 0; i <= 4; i++)
  {
    Semaforo semaforo[4] = {sem1, sem2, sem3, sem4};

    semaforo[i].allOn();
    t.Stop(1);
    semaforo[i].allOff();
  }
}



//* ===========================================================================
//* PROGRAMA ARDUINO
//* ===========================================================================


TestConexiones prueba;

void setup()
{
  prueba.begin(14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);
  prueba.testAll();
}

void loop()
{
}