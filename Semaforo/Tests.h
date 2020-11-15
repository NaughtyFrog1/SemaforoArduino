#ifndef Tests_h
#define Tests_h

#include "Semaforo.h"



// DEFINICIÓN DE LAS CLASES -------------------------------------------------->

class TestConexiones
{
  private:
    Semaforo s1, s2, s3, s4;
  public:
    TestConexiones(
      byte r1, byte a1, byte v1, 
      byte r2, byte a2, byte v2,
      byte r3, byte a3, byte v3,
      byte r4, byte a4, byte v4
    );
    void testAll();
};



// DECLARACIÓN DE LOS MÉTODOS ------------------------------------------------>

TestConexiones::TestConexiones(
  byte r1, byte a1, byte v1, 
  byte r2, byte a2, byte v2,
  byte r3, byte a3, byte v3,
  byte r4, byte a4, byte v4)
{
  s1.begin(r1, a1, v1, 0, 0);
  s2.begin(r2, a2, v2, 0, 0);
  s3.begin(r3, a3, v3, 0, 0);
  s4.begin(r4, a4, v4, 0, 0);
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


#endif
