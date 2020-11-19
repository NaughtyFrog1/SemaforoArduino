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
  esq.init();
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
  esq.init();
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

  esq1.setSemaforos(conexiones);
  esq2.setSemaforos(conexiones, 2);

  conex.testAll();
  esq1.init();
  esq2.init();
}

void loop() {
  esq1.secuencia();
  esq2.secuencia();
}
/**/


/* EsquinaPeatonal2 --------------------------------------------------------->
EsquinaPeatonal esq(2);

void setup() {
  Semaforo conexiones[4];
  conexiones[0] = Semaforo(14, 15, 16, 3000, 1000);
  conexiones[1] = Semaforo(17, 18, 19, 3000, 1000);
  conexiones[2] = Semaforo(12, 11, 10, 4000, 1000);
  conexiones[3] = Semaforo( 9,  8,  7, 4000, 1000);

  TestConexiones conex(4, conexiones);

  Semaforo lista_sem[2];
  SemaforoPeatonal lista_semP[2];

  lista_sem[0] = Semaforo(14, 15, 16, 3000, 1000);
  lista_sem[1] = Semaforo(12, 11, 10, 4000, 1000);
  
  lista_semP[0] = SemaforoPeatonal(17, 18);
  lista_semP[1] = SemaforoPeatonal( 9, 8);

  esq.setSemaforos(lista_sem, lista_semP);

  conex.testAll();
  esq.init();  
}

void loop() { esq.secuencia(); }
/**/


//* EsquinaMega -------------------------------------------------------------->


// Creamos las esquinas que deberá controlar el Arduino

EsquinaSimple   esqAv(4);  // Intersección de 4 calles (2 avenidas)
EsquinaPeatonal esq(2);    // Interseccion de 2 calles con cruce peatonal


void setup() {
  // Declaramos los distintos array que usaremos para pasar como argumento

  Semaforo lista_av[4];   // Para la avenida
  Semaforo lista_sem[2];  // Para los semáforos de la intersección con peatonal
  SemaforoPeatonal lista_semP[2];  // Cruces peatonales
  
  /*
    La forma en la que se crean los semáforos es la siguiente:
      - Semáforos de calle:
        Semaforo(pin_rojo, pin_ambar, pin_verde, tiempo_verde, tiempo_ambar)
      - Semáforos peatonales:
        SemaforoPeatonal(pin_no_cruce, pin_cruce)
  */

  lista_av[0] = Semaforo(/* pin, pin, pin, t, t */);
  lista_av[1] = Semaforo(/* pin, pin, pin, t, t */);
  lista_av[2] = Semaforo(/* pin, pin, pin, t, t */);
  lista_av[3] = Semaforo(/* pin, pin, pin, t, t */);

  lista_sem[0] = Semaforo(/* pin, pin, pin, t, t */);
  lista_sem[1] = Semaforo(/* pin, pin, pin, t, t */);
  
  lista_semP[0] = SemaforoPeatonal(/* pin, pin */);
  lista_semP[1] = SemaforoPeatonal(/* pint, pin */);


  // Indicamos que semáforos debera usar cada esquina

  esqAv.setSemaforos(lista_av);  
  esq.setSemaforos(lista_sem, lista_semP);


  // Encendemos las luces rojas de todos los semáforos

  esqAv.init();
  esq.init();  
}


void loop() {
  // Controlar la secuencia de las dos esquinas en forma simultanea
  esqAv.secuencia();
  esq.secuencia();
}
/**/
