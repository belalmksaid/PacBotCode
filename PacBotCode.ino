#include "Motor.h"
#include "Driver.h"
#include "Sensor.h"

//motor pins
#define RMOTA 20
#define RMOTB 21
#define LMOTA 23
#define LMOTB 22


//sensors
#define LSENSOR 0
#define RSENSOR 1
#define FSENSOR 0
#define BSENSOR 0

//other pins
#define GYROPIN 0


unsigned long dt = 0;
unsigned long pt = 0;

Motor motorRight(RMOTA, RMOTB);
Motor motorLeft(LMOTA, LMOTB);
Sensor front(FSENSOR, IR, &dt);
Sensor back(BSENSOR, IR, &dt);
Sensor right(RSENSOR, IRD, &dt);
Sensor left(LSENSOR, IR, &dt);
Gyro gyro(GYROPIN);

Driver driver(&motorLeft, &motorRight, &front, &back, &right, &left, &gyro, &dt);


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  // put your setup code here, to run once:
  pt = millis();
  driver.init();
  driver.setStraight();
}

int updateDelay = 10;
void loop() {
  // put your main code here, to run repeatedly:
  dt = millis() - pt;
  pt = millis();
  driver.update();
  // game logic here
  if(updateDelay <= 0) {
    driver.move();
  }
  else {
    updateDelay--;
  }
}
