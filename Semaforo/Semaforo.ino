#include <Arduino.h>
#include "Semaforo.h"
#include "Tests.h"


Esquina esq1;

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
}