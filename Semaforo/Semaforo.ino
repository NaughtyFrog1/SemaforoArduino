#include <Arduino.h>
#include "Semaforo.h"
#include "Tests.h"


/* Esquina
Esquina esq1(14, 15, 16, 5000, 1000,   // Semaforo 1.1
             17, 18, 19, 5000, 1000);  // Semáforo 1.2

Esquina esq2(12, 11, 10, 2000, 1000,   // Semaforo 2.1
              9,  8,  7, 2000, 1000);  // Semaforo 2.2
/**/


///* EsquinaCuatro
EsquinaCuatro esq1(14, 15, 16, 3000, 1000,   // Semaforo 1
                   17, 18, 19, 3000, 1000,   // Semáforo 2
                   12, 11, 10, 3000, 1000,   // Semáforo 3
                    9,  8,  7, 3000, 1000);  // Semáforo 4
/**/

void setup()
{ 
  TestConexiones conex(
    14, 15, 16,
    17, 18, 19,
    12, 11, 10,
     9,  8,  7
  );

  conex.testAll();
  esq1.todasRojo();
}

void loop()
{
  esq1.secuencia();
  // esq2.secuencia();  // Esquina
}
