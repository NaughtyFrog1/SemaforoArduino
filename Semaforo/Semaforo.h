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
    void begin(byte pin_luz);  // Para luz roja
    void begin(byte pin_luz, unit_t t);
    void on();
    void off();
    bool getSt();
    unit_t getTimeOn();
};

void LuzSemaforo::begin(byte pin_luz)
{
  pin = pin_luz;
  is_on = false;
  time_on = 0;
  pinMode(pin, OUTPUT);
}

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

bool LuzSemaforo::getSt() {return is_on;}

unit_t LuzSemaforo::getTimeOn() {return time_on;}


//· Semaforo ----------------------------------------------------------------->

class Semaforo
{
  private:
    LuzSemaforo rojo, ambar, verde;
  public:
    void begin(byte r, byte a, byte v, unit_t tv, unit_t ta);
    void allOn();
    void allOff();
    void setR();
    void setA();
    void setV();
    void setRA();
    bool getStR();
    bool getStA();
    bool getStV();
    unit_t getTimeOnV();
    unit_t getTimeOnA();
};

void Semaforo::begin(byte r, byte a, byte v, unit_t tv, unit_t ta)
{
  rojo.begin(r);
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

bool Semaforo::getStR() {return  rojo.getSt();}
bool Semaforo::getStA() {return ambar.getSt();}
bool Semaforo::getStV() {return verde.getSt();}

unit_t Semaforo::getTimeOnA() {return ambar.getTimeOn();}
unit_t Semaforo::getTimeOnV() {return verde.getTimeOn();}


//· Esquina ------------------------------------------------------------------>

class Esquina
{
  private:
   Semaforo sem1, sem2;
   byte step;
   unit_t last_step;
  public:
    Esquina();
    void Secuencia();
};


//! BORRAR: Solo para test rápidos
Esquina::Esquina()
{
  sem1.begin(14, 15, 16, 6000, 2000);
  sem2.begin(17, 18, 19, 4000, 2000);
  step = 0;
  last_step = 0;
}

void Esquina::Secuencia()
{
  
  if ((step == 0) && 
      (millis() > (last_step + sem1.getTimeOnV()))
  ){
    sem1.setV();
    sem2.setR();
    step++;
    last_step = millis();
  }

  else if ((step == 1) && 
           (millis() > (last_step + sem1.getTimeOnA()))
  ){
    sem1.setA();
    sem2.setRA();
    step++;
    last_step = millis();
  }

  else if ((step == 2) && 
      (millis() > (last_step + sem2.getTimeOnV()))
  ){
    sem2.setV();
    sem1.setR();
    step++;
    last_step = millis();
  }

  else if ((step == 3) && 
           (millis() > (last_step + sem2.getTimeOnA()))
  ){
    sem2.setA();
    sem1.setRA();
    step = 0;
    last_step = millis();
  }
}


#endif