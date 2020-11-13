#ifndef SemaforoCalle_h
#define SemaforoCalle_h

#include "Semaforo.h"



class EsquinaSimple : public Esquina {
  private:
    Semaforo sem[8];
    byte cant_sem;
    byte curr_sem;
    byte last_sem;
    byte max_step;
  
  public:
    EsquinaSimple(byte c);
    void setSemaforos(Semaforo s[]);
    void secuencia();
    void todasRojo();
};



EsquinaSimple::EsquinaSimple(byte c) {
  cant_sem = c;
  max_step = (cant_sem * 2) - 1;
  step = 0;
  last_step = 0;
  curr_sem = 0;
  last_sem = cant_sem - 1;
}

void EsquinaSimple::setSemaforos(Semaforo s[]) { 
  for (byte i = 0; i < cant_sem; i++)
    sem[i] = s[i];
}

void EsquinaSimple::todasRojo() {
  for (byte i = 0; i < cant_sem; i++)
    sem[i].setR();
}

void EsquinaSimple::secuencia() {
  for (byte stp = 0; stp <= max_step; stp += 2) {
    if ( 
      (step == stp)
      && (millis() > last_step + sem[last_sem].getTimeOnA())
    ){
      sem[curr_sem].setV();
      sem[last_sem].setR();

      step++;
      last_step = millis();
    }

    else if (
      (step == stp + 1)
      && (millis() > last_step + sem[curr_sem].getTimeOnV())
    ){
      sem[curr_sem].setA();
      sem[(curr_sem + 1) % cant_sem].setRA();

      step++;
      last_step = millis();
      last_sem = curr_sem;
      curr_sem++;
    }
  }
  if (step > max_step) {
    step = 0;
    last_sem = cant_sem - 1;
    curr_sem = 0;
  }
}


#endif