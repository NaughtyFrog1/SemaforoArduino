#ifndef Semaforo_h
#define Semaforo_h

typedef unsigned long unit_t; 



/* ============================================================================
  DECLARACIÓN DE LAS CLASES
============================================================================ */


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


class Esquina {
  protected:
    Semaforo sem[8];
    byte cant_sem;
    byte curr_sem;
    byte last_sem;
    byte max_step;
    byte step;
    unit_t last_step;
  public:
    virtual void secuencia();
    virtual void todasRojo();
};



/* ============================================================================
  DEFINICIÓN DE LOS MÉTODOS
============================================================================ */


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


//· Semaforo

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


#endif
