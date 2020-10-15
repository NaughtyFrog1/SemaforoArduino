#include <Arduino.h>



//* ===========================================================================
//* DECLARACIÓN DE CLASES
//* ===========================================================================


//· Timer -------------------------------------------------------------------->

class Timer
{
private:
  float base_time;
public:
  Timer();
  void SetBaseTime(float mult);
  void Stop(float x);
};

Timer::Timer()
{
  base_time = 1000;  // milisegundos a segundos
}

void Timer::SetBaseTime(float mult)
{
  base_time = mult * 1000;
}

void Timer::Stop(float time)
{
  delay(time * base_time);
}


//· LuzSemaforo -------------------------------------------------------------->

class LuzSemaforo
{
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

class Semaforo
{
  private:
    // ...
  public:
    LuzSemaforo rojo, ambar, verde;
    void begin(byte r, byte a, byte v);
    void allOn();
    void allOff();
    void setR();
    void setA();
    void setV();
    void setRA();
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

void Semaforo::setR()
{
  allOff();
  rojo.on();
}

void Semaforo::setA()
{
  allOff();
  ambar.on();
}

void Semaforo::setV()
{
  allOff();
  verde.on();
}

void Semaforo::setRA()
{
  allOff();
  rojo.on();
  ambar.on();
}



//* ===========================================================================
//* TESTS
//* ===========================================================================


//· TestConexiones ----------------------------------------------------------->

class TestConexiones
{
  private:
    Timer t;
    Semaforo s1, s2, s3, s4;
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
  s1.begin(r1, a1, v1);
  s2.begin(r2, a2, v2);
  s3.begin(r3, a3, v3);
  s4.begin(r4, a4, v4);
}

void TestConexiones::testAll()
{
  for (int i = 0; i < 4; i++)
  {
    Semaforo semaforo[4] = {s1, s2, s3, s4};

    semaforo[i].allOn();
    t.Stop(0.5);
    semaforo[i].allOff();
  }
}


//· TestEstados -------------------------------------------------------------->

class TestEstados
{
  private:
    Semaforo sem1;
  public:
    void begin(byte r, byte a, byte v);
    void endTest();
    void testR();
    void testA();
    void testV();
    void testRA();
};

void TestEstados::begin(byte r, byte a, byte v)
{
  sem1.begin(r, a, v);
}

void TestEstados::endTest()
{
  sem1.allOff();
}

void TestEstados::testR()
{
  sem1.setR();
}

void TestEstados::testA()
{
  sem1.setA();
}

void TestEstados::testV()
{
  sem1.setV();
}

void TestEstados::testRA()
{
  sem1.setRA();
}



//* ===========================================================================
//* PROGRAMA ARDUINO
//* ===========================================================================

Timer tm;

Semaforo sem1, sem2, sem3, sem4;
byte cont;


void setup()
{
  //· Tests ------------------------------------------------------------------>
  TestConexiones conex;
  TestEstados est;

  conex.begin(14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);
  conex.testAll();

  est.begin(14, 15, 16);
  est.testR();
  tm.Stop(1);
  est.testRA();
  tm.Stop(1);
  est.testV();
  tm.Stop(1);
  est.testA();
  tm.Stop(1);
  est.endTest();


  //· Programa --------------------------------------------------------------->
  
  sem1.begin(14, 15, 16);
  sem2.begin(17, 18, 19);
  sem3.begin(12, 11, 10);
  sem4.begin(9, 8, 7);
}

void loop()
{
  Semaforo esquina[4] = {sem1, sem2, sem3, sem4};

  esquina[(cont + 0) % 4].setV();
  esquina[(cont + 1) % 4].setR();
  esquina[(cont + 2) % 4].setR();
  esquina[(cont + 3) % 4].setR();
  tm.Stop(3);
  esquina[(cont + 0) % 4].setA();
  esquina[(cont + 1) % 4].setRA();
  tm.Stop(1);

  cont++;
  if (cont == 4) cont = 0;  // Reset para evitar overflow
}