#include <Arduino.h>
#include "EsquinaSimple.h"
#include "EsquinaPeatonal.h"
#include "Tests.h"



/* EsquinaSimple4 ------------------------------------------------------------>

EsquinaSimple esq(4);

void setup() { 
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


/* EsquinaSimple3 ------------------------------------------------------------>

EsquinaSimple esq(3);

void setup() { 
  TestConexiones conex( 14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);

  Semaforo lista_sem[4];
  lista_sem[0] = Semaforo(14, 15, 16, 3000, 1000);
  lista_sem[1] = Semaforo(17, 18, 19, 3000, 1000);
  lista_sem[2] = Semaforo(12, 11, 10, 3000, 1000);

  esq.setSemaforos(lista_sem);

  conex.testAll();
  esq.todasRojo();
}

void loop() {esq.secuencia();}
/**/


//* EsquinaSimple2x2 --------------------------------------------------------->

EsquinaSimple esq1(2), esq2(2);

void setup() { 
  TestConexiones conex( 14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);
  Semaforo lista_sem[2];

  lista_sem[0] = Semaforo(14, 15, 16, 3000, 1000);
  lista_sem[1] = Semaforo(17, 18, 19, 3000, 1000);
  esq1.setSemaforos(lista_sem);

  lista_sem[0] = Semaforo(12, 11, 10, 4000, 1000);
  lista_sem[1] = Semaforo( 9, 8, 7, 4000, 1000);
  esq2.setSemaforos(lista_sem);

  conex.testAll();
  esq1.todasRojo();
  esq2.todasRojo();
}

void loop() {
  esq1.secuencia();
  esq2.secuencia();
}
/**/
