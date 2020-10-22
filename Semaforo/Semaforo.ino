#include <Arduino.h>
#include "Semaforo.h"
#include "Tests.h"


Semaforo sem1, sem2, sem3, sem4;
byte cont;


void setup()
{
  //· Tests ------------------------------------------------------------------>
  TestConexiones conex;
  TestEstados est;

  Serial.begin(9600);
  conex.begin(14, 15, 16, 17, 18, 19, 12, 11, 10, 9, 8, 7);
  conex.testAll();

  est.begin(14, 15, 16);
  est.testSecuencia();


  //· Programa --------------------------------------------------------------->
  
  sem1.begin(14, 15, 16);
  sem2.begin(17, 18, 19);
  sem3.begin(12, 11, 10);
  sem4.begin(9, 8, 7);
}

void loop()
{
  Semaforo esquina[4] = {sem1, sem2, sem3, sem4};

  esquina[(cont + 0) % 4].setV();
  esquina[(cont + 1) % 4].setR();
  esquina[(cont + 2) % 4].setR();
  esquina[(cont + 3) % 4].setR();
  delay(3000);
  esquina[(cont + 0) % 4].setA();
  esquina[(cont + 1) % 4].setRA();
  delay(3000);

  cont++;
  if (cont == 3) cont = 0;  // Reset para evitar overflow
}