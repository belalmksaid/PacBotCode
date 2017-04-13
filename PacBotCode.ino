#include "Motor.h"
#include "Driver.h"
#include "Sensor.h"
#include "Schedule.h"
#include "Logic.h"
#include "Map.h"

//motor pins
#define RMOTA 22
#define RMOTB 23
#define LMOTA 20
#define LMOTB 21


//sensors
#define LSENSOR 18
#define RSENSOR 17
#define LDSENSOR 12
#define RDSENSOR 4
#define FSENSOR 19
#define BSENSOR 0

//other pins
#define GYROPIN 0

//commands
#define STOP 0
#define START 1
#define ASERIAL


Motor motorRight(RMOTA, RMOTB, 2, 3);
Motor motorLeft(LMOTA, LMOTB, 0, 1);
Sensor front(FSENSOR, IR);
Sensor back(BSENSOR, IR);
Sensor right(RSENSOR, IRSHORTR);
Sensor left(LSENSOR, IRSHORTL);
Sensor rightD(RDSENSOR, IRD);
Sensor leftD(LDSENSOR, IRD);
//GyroAccl gyro;

Driver driver(&motorLeft, &motorRight, &front, &back, &right, &left, &rightD, &leftD);
Schedule schedule(&driver, &front, &back, &right, &left, &rightD, &leftD);

Map gMap(&driver);
Logic logic(&driver, &gMap);

volatile short command = START;

void setup() {
  //Serial.begin(9600);
  //attachInterrupt(0, dmpDataReadyWrapper, RISING);
  schedule.init();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  driver.init();
  //while(!Serial) {}
  gMap.init(18, 19, 11, 12, UP);
  randomSeed(analogRead(A0));
  //delay(5000);
  //driver.setStraight();
  //driver.setAdjustState();
}

volatile int startUpTime = 50000;

void loop() {
  // game logic here
  if(startUpTime > 0) {
    schedule.updateSensorsOnly();
    startUpTime--;
  }
  else {
    getCommand();
    if(command == START) {
      schedule.update();
      logic.update();
    }
  }
}

void getCommand() {
  
}

/*void dmpDataReadyWrapper() {
  gyro.dmpDataReady();
}*/

