#include <Arduino.h>
#include "Semaforo.h"
#include "Tests.h"


/* EsquinaDos --------------------------------------------------------------->
EsquinaDos esq1(14, 15, 16, 5000, 1000,   // Semaforo 1.1
                17, 18, 19, 5000, 1000);  // Semáforo 1.2

EsquinaDos esq2(12, 11, 10, 2000, 1000,   // Semaforo 2.1
                 9,  8,  7, 2000, 1000);  // Semaforo 2.2

void setup() {
  TestConexiones conex( 14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);

  conex.testAll();
}

void loop() {esq1.secuencia(); esq2.secuencia();}
/**/



/* EsquinaCuatro ------------------------------------------------------------>
EsquinaCuatro esq(14, 15, 16, 3000, 1000,   // Semaforo 1
                  17, 18, 19, 3000, 1000,   // Semáforo 2
                  12, 11, 10, 3000, 1000,   // Semáforo 3
                   9,  8,  7, 3000, 1000);  // Semáforo 4

void setup() {
  TestConexiones conex( 14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);

  conex.testAll();
  esq.todasRojo();
}

void loop() {esq.secuencia();}
/**/



//* MuchiEsquinas ------------------------------------------------------------>
MuchiEsquinas esq(4);

void setup()
{ 
  TestConexiones conex( 14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);

  Semaforo lista_sem[4];
  lista_sem[0] = Semaforo(14, 15, 16, 3000, 1000);
  lista_sem[1] = Semaforo(17, 18, 19, 3000, 1000);
  lista_sem[2] = Semaforo(12, 11, 10, 3000, 1000);
  lista_sem[3] = Semaforo( 9,  8,  7, 3000, 1000);

  esq.setSemaforos(lista_sem);

  conex.testAll();
  esq.todasRojo();
}

void loop() {esq.secuencia();}
/**/
