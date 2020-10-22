#ifndef Semaforo_h
#define Semaforo_h

typedef unsigned long unit_t; 

//· LuzSemaforo -------------------------------------------------------------->

class LuzSemaforo
{
  private:
    byte pin;
    bool is_on;
    unit_t time_on;
  public:
    void begin(byte pin, unit_t t);
    void on();
    void off();
    bool getSt();
    unit_t getTimeOn();
};

void LuzSemaforo::begin(byte pin_luz, unit_t t)
{
  pin = pin_luz;
  is_on = false;
  time_on = t;
  pinMode(pin, OUTPUT);
}

void LuzSemaforo::on()
{
  digitalWrite(pin, HIGH);
  is_on = true;
}

void LuzSemaforo::off()
{
  digitalWrite(pin, LOW);
  is_on = false;
}

bool LuzSemaforo::getSt()
{
  return is_on;
}


//· Semaforo ----------------------------------------------------------------->

class Semaforo
{
  private:
    LuzSemaforo rojo, ambar, verde;
    unit_t last_change;
  public:
    void begin(byte r, byte a, byte v, unit_t tr, unit_t ta, unit_t tv);
    void allOn();
    void allOff();
    void setR();
    void setA();
    void setV();
    void setRA();
    bool getStR();
    bool getStA();
    bool getStV();
    unit_t getTimeOnR();
    unit_t getTimeOnA();
    unit_t getTimeOnV();
    unit_t getLastChange();

};

void Semaforo::begin(byte r, byte a, byte v, unit_t tr, unit_t ta, unit_t tv)
{
  rojo.begin(r, tr);
  ambar.begin(a, ta);
  verde.begin(v, tv);
}

void Semaforo::allOn()
{
  rojo.on();
  ambar.on();
  verde.on();
}

void Semaforo::allOff()
{
  rojo.off();
  ambar.off();
  verde.off();
}

void Semaforo::setR()
{
  allOff();
  rojo.on();
  last_change = millis();
}

void Semaforo::setA()
{
  allOff();
  ambar.on();
  last_change = millis();
}

void Semaforo::setV()
{
  allOff();
  verde.on();
  last_change = millis();
}

void Semaforo::setRA()
{
  allOff();
  rojo.on();
  ambar.on();
}

bool Semaforo::getStR() {return rojo.getSt();}
bool Semaforo::getStA() {return ambar.getSt();}
bool Semaforo::getStV() {return verde.getSt();}

unit_t Semaforo::getTimeOnR() {return rojo.getTimeOn();}
unit_t Semaforo::getTimeOnA() {return ambar.getTimeOn();}
unit_t Semaforo::getTimeOnV() {return verde.getTimeOn();}

unit_t Semaforo::getLastChange() {return last_change;}


#endif