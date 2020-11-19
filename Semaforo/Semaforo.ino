#include <Arduino.h>
#include "EsquinaSimple.h"
#include "EsquinaPeatonal.h"
#include "Tests.h"



/* EsquinaSimple4 ------------------------------------------------------------>

EsquinaSimple esq(4);

void setup() { 
  Semaforo conexiones[4];
  conexiones[0] = Semaforo(14, 15, 16, 3000, 1000);  // Sem 1
  conexiones[1] = Semaforo(17, 18, 19, 3000, 1000);  // Sem 2
  conexiones[2] = Semaforo(12, 11, 10, 4000, 1000);  // Sem 3
  conexiones[3] = Semaforo( 9, 8, 7, 4000, 1000);    // Sem 4

  TestConexiones conex(4, conexiones);
  esq.setSemaforos(conexiones);

  conex.testAll();
  esq.todasRojo();
}

void loop() {esq.secuencia();}
/**/


/* EsquinaSimple3 ------------------------------------------------------------>

EsquinaSimple esq(3);

void setup() { 
  Semaforo conexiones[4];
  conexiones[0] = Semaforo(14, 15, 16, 3000, 1000);  // Sem 1
  conexiones[1] = Semaforo(17, 18, 19, 3000, 1000);  // Sem 2
  conexiones[2] = Semaforo(12, 11, 10, 4000, 1000);  // Sem 3
  conexiones[3] = Semaforo( 9, 8, 7, 4000, 1000);    // Sem 4

  TestConexiones conex(4, conexiones);

  // Le pasamos un array con 4 elementos pero solo hará uso de los primeros 3
  // ya que al crear el objeto esq le indicamos que la esquina posee 3
  // semáforos
  // ¿Esto es un bug o una feature? Ninguna de las dos, es solo mi incapacidad
  // de crear arrays de tamaño dinámico y de conocer la cantidad de elementos
  // en un array mediante una función.
  esq.setSemaforos(conexiones);

  conex.testAll();
  esq.todasRojo();
}

void loop() {esq.secuencia();}
/**/


/* EsquinaSimple2x2 --------------------------------------------------------->

EsquinaSimple esq1(2), esq2(2);

void setup() { 
  Semaforo conexiones[4];
  conexiones[0] = Semaforo(14, 15, 16, 3000, 1000);  // Esq 1 Sem 1
  conexiones[1] = Semaforo(17, 18, 19, 3000, 1000);  // Esq 1 Sem 2
  conexiones[2] = Semaforo(12, 11, 10, 4000, 1000);  // Esq 2 Sem 1
  conexiones[3] = Semaforo( 9, 8, 7, 4000, 1000);    // Esq 2 Sem 2

  TestConexiones conex(4, conexiones);


  Semaforo lista_sem[2];

  lista_sem[0] = conexiones[0];
  lista_sem[1] = conexiones[1];
  esq1.setSemaforos(lista_sem);

  lista_sem[0] = conexiones[2];
  lista_sem[1] = conexiones[3];
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


//* EsquinaPeatonal2 --------------------------------------------------------->
EsquinaPeatonal esq(2);

void setup() {
  Semaforo conexiones[4];
  conexiones[0] = Semaforo(14, 15, 16, 3000, 1000); 
  conexiones[1] = Semaforo(17, 18, 19, 3000, 1000);
  conexiones[2] = Semaforo(12, 11, 10, 4000, 1000);
  conexiones[3] = Semaforo( 9, 8, 7, 4000, 1000);

  TestConexiones conex(4, conexiones);

  Semaforo lista_sem[2];
  SemaforoPeatonal lista_semP[2];

  lista_sem[0] = Semaforo(14, 15, 16, 3000, 1000);
  lista_sem[1] = Semaforo(12, 11, 10, 4000, 1000);
  
  lista_semP[0] = SemaforoPeatonal(17, 18);
  lista_semP[1] = SemaforoPeatonal(9, 8);

  esq.setSemaforos(lista_sem, lista_semP);

  conex.testAll();
  esq.todasRojo();  
}

void loop() { esq.secuencia(); }
/**/
