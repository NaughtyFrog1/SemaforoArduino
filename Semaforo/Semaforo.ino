#include <Arduino.h>
#include "Semaforo.h"
#include "Tests.h"


Esquina esq1(14, 15, 16, 5000, 1000,   // Semaforo 1
             17, 18, 19, 5000, 1000);  // Semáforo 2

Esquina esq2(12, 11, 10, 2000, 1000,   // Semaforo 3
              9,  8,  7, 2000, 1000);  // Semaforo 4

void setup()
{
  Serial.begin(9600);


  //· Tests ------------------------------------------------------------------>
  
  TestConexiones conex(
    14, 15, 16,
    17, 18, 19,
    12, 11, 10,
     9,  8,  7
  );
  TestEstados est(14, 15, 16);

  conex.testAll();
  est.testSecuencia();
}

void loop()
{
  esq1.Secuencia(); 
  esq2.Secuencia();
}