#include <Arduino.h>


class testLuces
{
private:
  byte pinLuz;
  
public:
  testLuces();
  void begin(byte pin);
  void on();
  void off();
};

testLuces::testLuces(/* args */)
{
  pinLuz = 0;
}

void testLuces::begin(byte pin)
{
  pinLuz = pin;
  pinMode(pinLuz, OUTPUT);
}

void testLuces::on() {
  digitalWrite(pinLuz, HIGH);
}

void testLuces::off() {
  digitalWrite(pinLuz, LOW);
}


testLuces led1, led2, led3;

void setup()
{
  led1.begin(12);
  led2.begin(11);
  led3.begin(10);
}

void loop()
{
  led1.on();
  delay(2000);
  led2.on();
  delay(1000);
  led1.off();
  led2.off();

  led3.on();
  delay(2000);
  led3.off();

  led2.on();
  delay(1000);
  led2.off();
}
