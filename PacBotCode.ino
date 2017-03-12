#include "Motor.h"
#include "Driver.h"
#include "Sensor.h"
#include "Schedule.h"

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

//commands
#define STOP 0
#define START 1


Motor motorRight(RMOTA, RMOTB);
Motor motorLeft(LMOTA, LMOTB);
Sensor front(FSENSOR, IR);
Sensor back(BSENSOR, IR);
Sensor right(RSENSOR, IRD);
Sensor left(LSENSOR, IR);
GyroAccl gyro;

Driver driver(&motorLeft, &motorRight, &front, &back, &right, &left, &gyro);
Schedule schedule(&driver, &front, &back, &right, &left, &gyro);

volatile short command = START;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, dmpDataReadyWrapper, RISING);
  schedule.init();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  driver.init();
  driver.setStraight();
  //driver.setAdjustState();
}

void loop() {
  // game logic here
  if(!gyro.isReady()) {
    schedule.updateSensorsOnly();
  }
  else {
    getCommand();
    if(command == START) {
      schedule.update();
    }
  }
}

void getCommand() {
  
}

void dmpDataReadyWrapper() {
  gyro.dmpDataReady();
}

