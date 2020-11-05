#ifndef Semaforo_h
#define Semaforo_h

typedef unsigned long unit_t; 


//· LuzSemaforo -------------------------------------------------------------->

class LuzSemaforo
{
  private:
    byte pin;
    unit_t time_on;
  public:
    void begin(byte pin_luz);  // Útil para inicializar una luz roja
    void begin(byte pin_luz, unit_t t);
    void on();
    void off();
    unit_t getTimeOn();
};

void LuzSemaforo::begin(byte pin_luz)
{
  pin = pin_luz;
  time_on = 0;
  pinMode(pin, OUTPUT);
}

void LuzSemaforo::begin(byte pin_luz, unit_t t)
{
  pin = pin_luz;
  time_on = t;
  pinMode(pin, OUTPUT);
}

void LuzSemaforo::on() {digitalWrite(pin, HIGH);}

void LuzSemaforo::off() {digitalWrite(pin, LOW);}

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
    Esquina(byte, byte, byte, unit_t, unit_t,
            byte, byte, byte, unit_t, unit_t);
    void Secuencia();
};

Esquina::Esquina(byte r1, byte a1, byte v1, unit_t tv1, unit_t ta1,
                 byte r2, byte a2, byte v2, unit_t tv2, unit_t ta2
){
  sem1.begin(r1, a1, v1, tv1, ta1);
  sem2.begin(r2, a2, v2, tv2, tv2);
  step = 0;
  last_step = 0;
}

void Esquina::Secuencia()
{
  if ((step == 0) && (millis() > (last_step + sem1.getTimeOnA())))
  {
    sem1.setV();
    sem2.setR();
    step++;
    last_step = millis();
  }

  else if ((step == 1) && (millis() > (last_step + sem1.getTimeOnV())))
  {
    sem1.setA();
    sem2.setRA();
    step++;
    last_step = millis();
  }

  else if ((step == 2) && (millis() > (last_step + sem2.getTimeOnA())))
  {
    sem2.setV();
    sem1.setR();
    step++;
    last_step = millis();
  }

  else if ((step == 3) && (millis() > (last_step + sem2.getTimeOnV())))
  {
    sem2.setA();
    sem1.setRA();
    step = 0;
    last_step = millis();
  }
}

/*
  TODO:
    Para solucionar el problema de los tiempos de las luces de los semáforos,
    tenemos que replantearnos la forma en la que contolamos la secuencia.

    Los ifs no tienen que cambiar con el tiempo de su luz, sino que con el 
    tiempo de la luz siguiente a la suya, puesto que estamos controlando cuando cambian, no cunado se encienden.
    
    Entonces si nosotros cambiamos a la luz verde, por ejemplo, le decimos a
    la luz ambar que espere el tiempo de la luz verde para encenderse
*/

#endif