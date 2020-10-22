#ifndef Tests_h
#define Tests_h

#include "Semaforo.h"


//· TestConexiones ----------------------------------------------------------->

class TestConexiones
{
  private:
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
  Semaforo semaforo[4] = {s1, s2, s3, s4};
  for (int i = 0; i < 4; i++)
  {
    semaforo[i].allOn();
    delay(500);
    semaforo[i].allOff();
  }
}


//· TestEstados -------------------------------------------------------------->

class TestEstados
{
  private:
    Semaforo sem1;
    void printStatuses();
  public:
    void begin(byte r, byte a, byte v);
    void endTest();
    void testR();
    void testA();
    void testV();
    void testRA();
    void testSecuencia();
};

void TestEstados::begin(byte r, byte a, byte v)
{
  sem1.begin(r, a, v);
}

void TestEstados::printStatuses()
{
  Serial.println();
  Serial.print("R = "); Serial.println(sem1.getStR());
  Serial.print("A = "); Serial.println(sem1.getStA());
  Serial.print("V = "); Serial.println(sem1.getStV());
}

void TestEstados::endTest()
{
  sem1.allOff();
}

void TestEstados::testR()
{
  sem1.setR();
  printStatuses();
}

void TestEstados::testA()
{
  sem1.setA();
  printStatuses();
}

void TestEstados::testV()
{
  sem1.setV();
  printStatuses();
}

void TestEstados::testRA()
{
  sem1.setRA();
  printStatuses();
}

void TestEstados::testSecuencia()
{
  testR(); 
  delay(1000);
  testRA();
  delay(1000);
  testV();
  delay(1000);
  testA();
  delay(1000);
  endTest();
}

#endif