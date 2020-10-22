#ifndef Semaforo_h
#define Semaforo_h


//· LuzSemaforo -------------------------------------------------------------->

class LuzSemaforo
{
  private:
    byte pin;
    bool is_on;
  public:
    void begin(byte pin);
    void on();
    void off();
    bool getSt();
};

void LuzSemaforo::begin(byte pin_luz)
{
  pin = pin_luz;
  is_on = false;
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
  public:
    void begin(byte r, byte a, byte v);
    void allOn();
    void allOff();
    void setR();
    void setA();
    void setV();
    void setRA();
    bool getStR();
    bool getStA();
    bool getStV();
};

void Semaforo::begin(byte r, byte a, byte v)
{
  rojo.begin(r);
  ambar.begin(a);
  verde.begin(v);
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
}

void Semaforo::setA()
{
  allOff();
  ambar.on();
}

void Semaforo::setV()
{
  allOff();
  verde.on();
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

#endif