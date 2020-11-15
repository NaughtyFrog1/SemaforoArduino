/*
  EsquinaSimple.h

  En este archivo de cabecera se encuentran todas las clases que le permiten al
  programa la posibilidad de poder controlar varios semáforos en una misma
  esquina y múltiples esquinas a la vez, sin hacer uso de semáforos peatonales
*/

#ifndef EsquinaSimple_h
#define EsquinaSimple_h

#include "Semaforo.h"



// DECLARACIÓN DE LAS CLASES ------------------------------------------------->


class EsquinaSimple : public Esquina {
  public:
    EsquinaSimple(byte c);
    void setSemaforos(Semaforo s[]);
    void secuencia();
    void todasRojo();
};



// DEFINICIÓN DE LOS MÉTODOS ------------------------------------------------->


EsquinaSimple::EsquinaSimple(byte c) {
  // Determinar la cantidad de semaforos que habrá en la esquina y en base a
  // eso dar valor a las propiedades del objeto

  cant_sem = c;
  max_step = (cant_sem * 2) - 1;
  last_sem = cant_sem - 1;

  step = 0;
  last_step = 0;
  curr_sem = 0;
}

void EsquinaSimple::setSemaforos(Semaforo s[]) {
  // Recibe como argumento un array con los Semaforos que debe utilizar para
  // realizar la secuencia

  for (byte i = 0; i < cant_sem; i++)
    sem[i] = s[i];
}

void EsquinaSimple::todasRojo() {
  // Poner en rojo todos los semáforos de la esquina

  for (byte i = 0; i < cant_sem; i++)
    sem[i].setR();
}

void EsquinaSimple::secuencia() {
  // Controlar la secuencia de todos los semáforos en la esquina. 
  // Esta es quizas la parte más importante de todo el programa. Aquí todo lo
  // definido en el archivo Semaforo.h es utilizado para poder controlar la 
  // secuencia de los semáforos de toda una esquina y de forma 'asincrona'
  // (sin hacer que el Arduino detenga su ejecución el tiempo que deben
  // permanecer encendidas las luces).


  for (byte stp = 0; stp <= max_step; stp += 2) {
      // Para cambiar de luz verifica en que paso de la secuencia está y que el
      // tiempo transcurrido sea mayor al tiempo que debe permanecer encendida 
      // la luz anterior
    if ( 
      // Si el step es par, se cambia el semaforo anterior en la secuancia a
      // rojo y se pone en verde el actual
      (step == stp)
      && (millis() > last_step + sem[last_sem].getTimeOnA())
    ){
      sem[curr_sem].setV();
      sem[last_sem].setR();

      step++;
      last_step = millis();
    }

    else if (
      // Si el step es impar, se pone en ámbar el semáforo actual en la
      // secuencia y en rojo y ámbar el semáforo siguiente. Luego se actualizan
      // los valores de los flags curr_sem y last_sem
      (step == stp + 1)
      && (millis() > last_step + sem[curr_sem].getTimeOnV())
    ){
      sem[curr_sem].setA();
      sem[(curr_sem + 1) % cant_sem].setRA();

      last_sem = curr_sem;
      curr_sem++;
      step++;
      last_step = millis();
    }
  }
  if (step > max_step) {
    // Al llegar al máximo de steps (que equivale a realizar todo un ciclo de
    // la secuencia) se reinician los flags que controlan el estado de la misma
    step = 0;
    last_sem = cant_sem - 1;
    curr_sem = 0;
  }
}


#endif