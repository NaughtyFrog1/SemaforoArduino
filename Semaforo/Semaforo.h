#ifndef Semaforo_h
#define Semaforo_h

//* ===========================================================================
//* DECLARACIÓN DE CLASES
//* ===========================================================================


//· Timer -------------------------------------------------------------------->

class Timer
{
private:
  float base_time;
public:
  Timer();
  void SetBaseTime(float mult);
  void Stop(float x);
};

Timer::Timer()
{
  base_time = 1000;  // milisegundos a segundos
}

void Timer::SetBaseTime(float mult)
{
  base_time = mult * 1000;
}

void Timer::Stop(float time)
{
  delay(time * base_time);
}


//· LuzSemaforo -------------------------------------------------------------->

class LuzSemaforo
{
  private:
    byte pin;
  public:
    void begin(byte pin);
    void on();
    void off();
};

void LuzSemaforo::begin(byte pin_luz)
{
  pin = pin_luz;
  pinMode(pin, OUTPUT);
}

void LuzSemaforo::on()
{
  digitalWrite(pin, HIGH);
}

void LuzSemaforo::off()
{
  digitalWrite(pin, LOW);
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

#endif