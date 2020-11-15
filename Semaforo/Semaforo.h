/*
  Semaforo.h

  En este archivo de cabecera se encuentran todas las clases base de las que
  luego heredarán las demás clases del programa.

  En este archivo se definen cuatro clases: Luz, LuzSemaforo, Semaforo y
  Esquina.

  A la hora de crear nuevas funcionalidades no se debería tener la necesidad de
  realizar cambios en este archivo, pudiendo así garantizar que los cambios
  hechos en una parte del programa no afectarán al funcionamiento de las demás
  clases.
*/


#ifndef Semaforo_h
#define Semaforo_h

// Definimos un nombre alternativo al tipo de dato que retorna millis()
typedef unsigned long unit_t; 



/* ============================================================================
  DECLARACIÓN DE LAS CLASES
============================================================================ */


class Luz {
  protected:
    byte pin;  // Pin donde va conectada la luz
    boolean estado;  // Flag que permite conocer el estado de la luz
  public:
    void begin(byte p);
    void on();
    void off();
    boolean isOn();
};


class LuzSemaforo : public Luz {
  private:
    unit_t time_on;  // Tiempo que debe permanecer encendida la luz
  public:
    void begin(byte p, unit_t t);
    unit_t getTimeOn();
};


class Semaforo {
  private:
    // Luz ambar y verde del semáforo
    LuzSemaforo ambar, verde;
    // Luz roja del semáforo, al no llevar un tiempo de encendio es del tipo
    // Luz, que no lleva control de tiempo
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
    // Semáforos que debe controlar la esquina. El máximo de 8 es una elección
    // arbitraria que surge por la falta de arrays dinámicos.
    Semaforo sem[8];
    byte cant_sem;     // Cantidad de semáforos que tiene la esquina
    byte curr_sem;     // Indice del semáforo que se debe modificar
    byte last_sem;     // Indice del último semáforo en ser modificado
    byte step;         // Registro de en que paso de la secuencia esta
    byte max_step;     // Cantidad de pasos que tiene la secuencia
    unit_t last_step;  // Tiempo en el que se produjo la última modificación
  public:
    virtual void secuencia();
    virtual void todasRojo();
};



/* ============================================================================
  DEFINICIÓN DE LOS MÉTODOS
============================================================================ */


//· Luz

void Luz::begin(byte p) {
  // Inicializar el objeto Luz e indicar a que pin va conectado.

  pin = p;
  estado = false;
  pinMode(pin, OUTPUT);
}

void Luz::on() {
  // Encender la luz

  digitalWrite(pin, HIGH);
  estado = true;  
}

void Luz::off() {
  // Apagar la luz

  digitalWrite(pin, LOW);
  estado = false;
}

boolean Luz::isOn() {
  // Informar si la luz esta encendida o apagada

  return estado;
}  


//· LuzSemaforo

void LuzSemaforo::begin(byte p, unit_t t) {
  // Inicializar el objeto LuzSemaforo e indicar a que pin va conectado y
  // cuanto tiempo debe permanecer encendida la luz.

  pin = p;
  time_on = t;
  estado = false;
  pinMode(pin, OUTPUT);
}

unit_t LuzSemaforo::getTimeOn() {
  // Informar cuanto tiempo debe permanecer encendida la luz

  return time_on;
}


//· Semaforo

Semaforo::Semaforo() {
  // Constructor vacío
  // Útil para cuando se desea inicializar con el método .begin()
}

Semaforo::Semaforo(byte r, byte a, byte v, unit_t tv, unit_t ta) {
  // Constructor que permite inicializar las luces del semaforo desde una
  // instanciación de la clase.
  // Útil para pasar objetos temporales

  begin(r, a, v, tv, ta);
}

void Semaforo::begin(byte r, byte a, byte v, unit_t tv, unit_t ta) {
  // Inicializar todas las luces del semáforo, indicando a que pines deben
  // ir conenctadas y cuanto tiempo deben permanecer encendidas ( en caso de
  // ser necesario)

  rojo.begin(r);
  ambar.begin(a, ta);
  verde.begin(v, tv);
}

void Semaforo::allOn() {
  // Encender todas las lúces del semáforo.
  // Útil para testear conexiones

  rojo.on();
  ambar.on();
  verde.on();
}

void Semaforo::allOff() {
  // Apagar todas las lúces del semáforo

  rojo.off();
  ambar.off();
  verde.off();
}

void Semaforo::setR() {
  // Poner el semáforo en rojo

  allOff();
  rojo.on();
}

void Semaforo::setA() {
  // Poner el semáforo en ámbar/amarillo

  allOff();
  ambar.on();
}

void Semaforo::setV() {
  // Poner el semáforo en verde

  allOff();
  verde.on();
}

void Semaforo::setRA() {
  // Poner el semáforo en rojo y ámbar

  allOff();
  rojo.on();
  ambar.on();
}

unit_t Semaforo::getTimeOnA() {
  // Informar el tiempo que debe permanecer encendida la luz ámbar

  return ambar.getTimeOn();
}

unit_t Semaforo::getTimeOnV() {
  // Informar el tiempo que debe permanecer encendida la luz roja
  
  return verde.getTimeOn();
}


#endif
