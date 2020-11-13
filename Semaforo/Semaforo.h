#ifndef Semaforo_h
#define Semaforo_h

typedef unsigned long unit_t; 



/* ============================================================================
  DECLARACIÓN DE LAS CLASES
============================================================================ */


//* Luz ---------------------------------------------------------------------->

class Luz {
  protected:
    byte pin;
    boolean estado;
  public:
    void begin(byte p);
    void on();
    void off();
    boolean getEstado();
};

class LuzSemaforo : public Luz {
  private:
    unit_t time_on;
  public:
    void begin(byte p, unit_t t);
    unit_t getTimeOn();
};


//* Semaforo ----------------------------------------------------------------->

class Semaforo {
  private:
    LuzSemaforo ambar, verde;
    Luz rojo;
  public:
    Semaforo();
    Semaforo(byte r, byte a, byte v, unit_t tv, unit_t ta);
    void begin(byte r, byte a, byte v, unit_t tv, unit_t ta);
    void allOn();
    void allOff();
    void setR();
    void setA();
    void setV();
    void setRA();
    unit_t getTimeOnV();
    unit_t getTimeOnA();
};


//* Esquina ------------------------------------------------------------------>

class Esquina {
  protected:
    byte step;
    unit_t last_step;
  public:
    virtual void secuencia();
    virtual void todasRojo();
};

class MuchiEsquinas : public Esquina {
  private:
    Semaforo sem[8];
    byte cant_sem;
    byte curr_sem;
    byte last_sem;
    byte max_step;
  
  public:
    MuchiEsquinas(byte c);
    void setSemaforos(Semaforo s[]);
    void secuencia();
    void todasRojo();
};



/* ============================================================================
  DEFINICIÓN DE LOS MÉTODOS
============================================================================ */


//* LUZ ---------------------------------------------------------------------->

//· Luz

void Luz::begin(byte p) {
  pin = p;
  estado = false;
  pinMode(pin, OUTPUT);
}

void Luz::on() {
  digitalWrite(pin, HIGH);
  estado = true;  
}

void Luz::off() {
  digitalWrite(pin, LOW);
  estado = false;
}

boolean Luz::getEstado() {return estado;}


//· LuzSemaforo

void LuzSemaforo::begin(byte p, unit_t t) {
  pin = p;
  time_on = t;
  estado = false;
  pinMode(pin, OUTPUT);
}

unit_t LuzSemaforo::getTimeOn() {return time_on;}


//* Semaforo ----------------------------------------------------------------->

Semaforo::Semaforo() {}

Semaforo::Semaforo(byte r, byte a, byte v, unit_t tv, unit_t ta) {
  begin(r, a, v, tv, ta);
}

void Semaforo::begin(byte r, byte a, byte v, unit_t tv, unit_t ta) {
  rojo.begin(r);
  ambar.begin(a, ta);
  verde.begin(v, tv);
}

void Semaforo::allOn() {
  rojo.on();
  ambar.on();
  verde.on();
}

void Semaforo::allOff() {
  rojo.off();
  ambar.off();
  verde.off();
}

void Semaforo::setR() {
  allOff();
  rojo.on();
}

void Semaforo::setA() {
  allOff();
  ambar.on();
}

void Semaforo::setV() {
  allOff();
  verde.on();
}

void Semaforo::setRA() {
  allOff();
  rojo.on();
  ambar.on();
}

unit_t Semaforo::getTimeOnA() {return ambar.getTimeOn();}

unit_t Semaforo::getTimeOnV() {return verde.getTimeOn();}


//* Esquina ------------------------------------------------------------------>

//· MuchiEsquinas

MuchiEsquinas::MuchiEsquinas(byte c) {
  cant_sem = c;
  max_step = (cant_sem * 2) - 1;
  step = 0;
  last_step = 0;
  curr_sem = 0;
  last_sem = cant_sem - 1;
}

void MuchiEsquinas::setSemaforos(Semaforo s[]) { 
  for (byte i = 0; i < cant_sem; i++)
    sem[i] = s[i];
}

void MuchiEsquinas::todasRojo() {
  for (byte i = 0; i < cant_sem; i++)
    sem[i].setR();
}

void MuchiEsquinas::secuencia() {
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
