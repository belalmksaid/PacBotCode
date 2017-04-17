#include <SoftwareSerial.h>

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
#define RX 9
#define TX 10

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

SoftwareSerial xbee(RX, TX);
Queue<char> commandQ;

volatile short command = START;

void setup() {
  schedule.init();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  driver.init();
  gMap.init(14, 14, 23, 24, LEFT);
  randomSeed(analogRead(A0));
  xbee.begin(9600);
  testing();
}

volatile int startUpTime = 50000;

void loop() {
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

char tempQ;
void getCommand() {
  if(xbee.available() > 0) {
    tempQ = xbee.read();
    if(tempQ != ';')
      commandQ.push(tempQ);
    else
      interpret();  
  }
}

void interpret() {
  while(commandQ.size > 0) {
    Serial.print(commandQ.pop());
  }
  Serial.println();
  commandQ.reset();
}

void testing() {
  Serial.println("testing");
  unsigned long a = micros(); 
    logic.simpleAI();
  a = micros()- a;
  Serial.println(a);
}
