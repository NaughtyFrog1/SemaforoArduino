#ifndef Tests_h
#define Tests_h

#include "Semaforo.h"



// DEFINICIÓN DE LAS CLASES -------------------------------------------------->

class TestConexiones {
  private:
    Semaforo semaforo[8];
    byte cant_sem;
  public:
    TestConexiones(byte cant_sem, Semaforo sem[]);
    void testAll();
};



// DECLARACIÓN DE LOS MÉTODOS ------------------------------------------------>

TestConexiones::TestConexiones(byte cant, Semaforo sem[]) {
  cant_sem = cant;
  for (byte i = 0; i < cant_sem; i++) {
    semaforo[i] = sem[i];
  }
  
}

void TestConexiones::testAll() {
  for (int i = 0; i < cant_sem; i++) {
    semaforo[i].allOn();
    delay(500);
    semaforo[i].allOff();
  }
}


#endif
