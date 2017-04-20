#include <SoftwareSerial.h>

#include "Motor.h"
#include "Driver.h"
#include "Sensor.h"
#include "Schedule.h"
#include "Logic.h"
#include "Map.h"


//motor pins
#define RMOTA 23
#define RMOTB 22
#define LMOTA 21
#define LMOTB 20


//sensors
#define LSENSOR 17
#define RSENSOR 16
#define LDSENSOR 5
#define RDSENSOR 4
#define FSENSOR 18
#define BSENSOR 0

//other pins
#define RX 9
#define TX 10

//commands
#define STOP 0
#define START 1
#define ASERIAL


Motor motorRight(RMOTA, RMOTB, 1, 0);
Motor motorLeft(LMOTA, LMOTB, 3, 2);
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
  gMap.init(15, 16, 29, 30, RIGHT);
  randomSeed(analogRead(A0));
  xbee.begin(9600);
  //while(!Serial) { }
  //testing();
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

void reset() {
  gMap.init(14, 14, 23, 24, LEFT);
  gMap.reset();
  driver.status = SLEEP;
}

void testing() {
  Serial.println("testing");
//  vector<5> p;
//   p[0] = 26;
//   p[1] = 27;
//   p[2] = 20;
//   p[3] = 21  ;
//   vector<5> d;
//   d[0] = 26;
//   d[1] = 27;
//   d[2] = 8;
//   d[3] = 9;
//   PathAl g;
//   vector<2> dir;
//   dir[0] = 0;
//   dir[1] = -1;
//   vector<5> n;
//   g.projectMod(p, dir, &gMap, 0, &n);
//   unsigned long a = micros();
//   g.shortestPathD(p, d, &gMap);
//  //unsigned long a = micros(); 
//  //logic.simpleAI();
//  a = micros()- a;
//  Serial.println(a);
  Pos a(9, 10, 17, 18, RIGHT);
  Pos b(18, 19, 17, 18, LEFT);
  gMap.eatFood(&a, &b);
    }
