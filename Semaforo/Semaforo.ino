#include <Arduino.h>
#include "Semaforo.h"
#include "Tests.h"


/* MuchiEsquinas4 ----------------------------------------------------------->
MuchiEsquinas esq(4);

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


/* MuchiEsquinas3 ----------------------------------------------------------->
MuchiEsquinas esq(3);

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

//* MuchiEsquinas2x2 --------------------------------------------------------->
MuchiEsquinas esq1(2), esq2(2);

void setup() { 
  TestConexiones conex( 14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);

  Semaforo lista_sem_esq1[2];
  lista_sem_esq1[0] = Semaforo(14, 15, 16, 3000, 1000);
  lista_sem_esq1[1] = Semaforo(17, 18, 19, 3000, 1000);

  esq1.setSemaforos(lista_sem_esq1);

  Semaforo lista_sem_esq2[2];
  lista_sem_esq2[0] = Semaforo(12, 11, 10, 4000, 1000);
  lista_sem_esq2[1] = Semaforo( 9, 8, 7, 4000, 1000);

  esq1.setSemaforos(lista_sem_esq1);
  esq2.setSemaforos(lista_sem_esq2);

  conex.testAll();
  esq1.todasRojo();
  esq2.todasRojo();
}

void loop() {
  esq1.secuencia();
  esq2.secuencia();
}
/**/