/*
  EsquinaPeatonal.h

  En este archivo de cabecera se encuentran todas las clases que le permiten al
  programa la posibilidad de poder controlar varios semáforos en una misma
  esquina y múltiples esquinas a la vez, con cruces peatonales
*/


#ifndef EsquinaPeatonal_h
#define EsquinaPeatonal_h

#include "Semaforo.h"



// DEFINICIÓN DE LAS CLASES -------------------------------------------------->


class SemaforoPeatonal {
  private:
    Luz no_cruce, cruce;  // Luces que conforman el semaforo
  public:
    SemaforoPeatonal();
    SemaforoPeatonal(byte nc, byte c);
    void begin(byte nc, byte c);
    void allOn();
    void allOff();
    void setCruce();
    void setNoCruce();
}; 

class EsquinaPeatonal : public Esquina {
  private:
    // Semáforos peatonales que debe controlar la esquina
    SemaforoPeatonal semP[8];
    // Flag que indica cual es el siguiente semáforo en la secuencia
    byte next_sem;
  public:
    EsquinaPeatonal(byte c);
    void setSemaforos(Semaforo s[], SemaforoPeatonal p[]);
    void setSemaforos(
      Semaforo s[], byte pos_s,  SemaforoPeatonal p[], byte pos_p
    );
    void secuencia();
    void init();
};



// DECLARACIÓN DE LOS MÉTODOS ------------------------------------------------>


//· SemaforoPeatonal

SemaforoPeatonal::SemaforoPeatonal() {
  // Constructor vacio
  // Útil cuando se desea inicializar con el método .begin()
}

SemaforoPeatonal::SemaforoPeatonal(byte nc, byte c) {
  // Constructor que permite inicializar las luces del semáforo peatonal,
  // indicanto a que pines deben ir conectadas.
  // Útil para pasar objetos temporales

  begin(nc, c);
}

void SemaforoPeatonal::begin(byte nc, byte c) {
  // Inicializar las luces del semáforo, indicando a que pines deben ir 
  // conectadas

  no_cruce.begin(nc);
  cruce.begin(c);
}

void SemaforoPeatonal::allOn() {
  // Encender todas las luces del semáforo peatonal

  no_cruce.on();
  cruce.on();
}

void SemaforoPeatonal::allOff() {
  // Apagar todas las luces del semáforo peatonal

  no_cruce.off();
  cruce.off();
}

void SemaforoPeatonal::setNoCruce() {
 // Poner el semáforo peatonal en `No Cruce'

  no_cruce.on();
  cruce.off();
}

void SemaforoPeatonal::setCruce() {
  // Poner el semáforo peatonal en 'Cruce'

  no_cruce.off();
  cruce.on();
}


//· EsquinaPeatonal
/*
  Esta clase funciona de forma muy similar a la clase EsquinaSimple, por lo que
  la mayoría de los métodos hacen lo mismo solo que le añaden la funcionalidad
  de los semáforos peatonales
*/

EsquinaPeatonal::EsquinaPeatonal(byte c) {
  // Determinar la cantidad de semaforos que habrá en la esquina y en base a
  // eso dar valor a las propiedades del objeto

  cant_sem = c;
  max_step = (cant_sem * 2) - 1;
  last_sem = cant_sem - 1;

  step = 0;
  last_step = 0;
  curr_sem = 0;
  next_sem = 1;
}

void EsquinaPeatonal::setSemaforos(Semaforo s[], SemaforoPeatonal p[]) {
  // Recibe como argumento dos arrays, en uno se debe indicar que semáforos
  // debe utilizar para la secuencia, en otro los semáforos peatonales.
  // Es importante que el semáforo este en el mismo índice que el semáforo
  // peatonal que le corresponde para que el programa funcione adecuadamente

  for (byte i = 0; i < cant_sem; i++) {
    sem[i] = s[i];
    semP[i] = p[i];
  }
}

void EsquinaPeatonal::setSemaforos(
  Semaforo s[], byte pos_s,  SemaforoPeatonal p[], byte pos_p
){
  // Recibe cuatro argumentos de entrada. Se indica el array de semáforos y la
  // posición desde la que debe empezar y el array de los semáforos peatonales
  // y el índice desde el que debe empezar

  byte offset_s = pos_s + cant_sem;
  byte offset_p = pos_p + cant_sem;
  byte i = 0;

  for (byte x = pos_s; x < offset_s; x++) {
    sem[i] = s[x];
    i++;
  }
  i = 0;
  for (byte x = pos_p; x < offset_p; x++) {
    semP[i] = p[x];
    i++;
  }
  
}

void EsquinaPeatonal::init() {
  // Poner en rojo todos los semáfotos y cruces peatonales

  for (byte i = 0; i < cant_sem; i++) {
    sem[i].setR();
    semP[i].setNoCruce();
  }
  
}

void EsquinaPeatonal::secuencia() {
  // Similar al método secuencia de la clase EsquinaSimple, pero se agregan los
  // semáforos peatonales a la secuencia
  
  for (byte stp = 0; stp <= max_step; stp += 2) {
    if ( 
      (step == stp)
      && (millis() > last_step + sem[last_sem].getTimeOnA())
    ){
      sem[curr_sem].setV();
      sem[last_sem].setR();

      semP[curr_sem].setNoCruce();
      semP[last_sem].setCruce();

      step++;
      last_step = millis();
    }

    else if (
      (step == stp + 1)
      && (millis() > last_step + sem[curr_sem].getTimeOnV())
    ){
      sem[curr_sem].setA();
      sem[next_sem].setRA();

      semP[last_sem].setNoCruce();
      semP[next_sem].setNoCruce();


      last_sem = curr_sem;
      curr_sem++;
      step++;
      next_sem = (curr_sem + 1) % cant_sem;
      last_step = millis();
    }
  }
  if (step > max_step) {
    step = 0;
    last_sem = cant_sem - 1;
    curr_sem = 0;
  }
}


#endif
