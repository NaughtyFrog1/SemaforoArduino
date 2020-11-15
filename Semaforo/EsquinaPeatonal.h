#ifndef EsquinaPeatonal_h
#define EsquinaPeatonal_h

#include "Semaforo.h"



// DEFINICIÓN DE LAS CLASES -------------------------------------------------->


class SemaforoPeatonal {
  public:
    SemaforoPeatonal();
    void begin();
    void setCruce();
    void setNoCruce();
}; 

class EsquinaPeatonal : public Esquina {
  private:
    SemaforoPeatonal semP[8];
  public:
    EsquinaPeatonal(byte c);
    void setSemaforos(Semaforo s[]);
    void setPeatonales(Luz l[]);
    
    void secuencia();
    void todasRojo();
};



// DECLARACIÓN DE LOS MÉTODOS ------------------------------------------------>


// Code...


#endif
