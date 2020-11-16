/*
  Test.h

  En este archivo de cabecera se encuentran todas las clases destinadas a
  realizar pruebas sobre el funcionamiento del programa y las conexiones de la
  instalación
*/


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
  // Recibe como argumento la cantidad de semaforos de la esquina y un array
  // con los semaforos que debe utilizar
  cant_sem = cant;
  for (byte i = 0; i < cant_sem; i++) {
    semaforo[i] = sem[i];
  }
  
}

void TestConexiones::testAll() {
  // Encender en simultaneo todas las luces de un semáforo, esperar un tiempo,
  // apagarlas y pasar al siguiente semáforo

  for (byte i = 0; i < cant_sem; i++) {
    semaforo[i].allOn();
    delay(500);
    semaforo[i].allOff();
  }
}


#endif
