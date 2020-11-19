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
    Luz no_cruce, cruce;
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
    SemaforoPeatonal semP[8];
  public:
    EsquinaPeatonal(byte c);
    void setSemaforos(Semaforo s[], SemaforoPeatonal p[]);
    void secuencia();
    void todasRojo();
};



// DECLARACIÓN DE LOS MÉTODOS ------------------------------------------------>


//· SemaforoPeatonal

SemaforoPeatonal::SemaforoPeatonal() { }

SemaforoPeatonal::SemaforoPeatonal(byte nc, byte c) {
  begin(nc, c);
}

void SemaforoPeatonal::begin(byte nc, byte c) {
  no_cruce.begin(nc);
  cruce.begin(c);
}

void SemaforoPeatonal::allOn() {
  no_cruce.on();
  cruce.on();
}

void SemaforoPeatonal::allOff() {
  no_cruce.off();
  cruce.off();
}

void SemaforoPeatonal::setNoCruce() {
  no_cruce.on();
  cruce.off();
}

void SemaforoPeatonal::setCruce() {
  no_cruce.off();
  cruce.on();
}


//· EsquinaPeatonal

EsquinaPeatonal::EsquinaPeatonal(byte c) {
  cant_sem = c;
  max_step = (cant_sem * 2) - 1;
  last_sem = cant_sem - 1;

  step = 0;
  last_step = 0;
  curr_sem = 0;
}

void EsquinaPeatonal::setSemaforos(Semaforo s[], SemaforoPeatonal p[]) {
  for (byte i = 0; i < cant_sem; i++) {
    sem[i] = s[i];
    semP[i] = p[i];
  }
}

void EsquinaPeatonal::todasRojo() {
  for (byte i = 0; i < cant_sem; i++) {
    sem[i].setR();
    semP[i].setCruce();
  }
  
}

void EsquinaPeatonal::secuencia() {
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
      sem[(curr_sem + 1) % cant_sem].setRA();

      semP[(curr_sem + 1) % cant_sem].setNoCruce();


      last_sem = curr_sem;
      curr_sem++;
      step++;
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
