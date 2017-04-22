#include <SoftwareSerial.h>
#include <string.h>


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
#define FSENSOR 15
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
//Queue<char> commandQ;
char currCString[200];
//char* currString = malloc(200*sizeof(char));
//currString[0] = '\0';
//String currString;

volatile short command = START;

void setup() {
  schedule.init();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  driver.init();
  gMap.init(12, 13, 23, 24, UP);
  randomSeed(analogRead(A0));
  xbee.begin(9600);
  //while(!Serial) { }

  //testing();
}

volatile int startUpTime = 2000;

void loop() {
  if(startUpTime > 0) {
    schedule.updateSensorsOnly();
    //xxbee.println(startUpTime);
    startUpTime--;
  }
  else {
    //getCommand();
    if(command == START) {
      schedule.update();
      logic.update();
      Serial.println(front.distance);
    }
    else if(command == STOP) {
      driver.freeze();
    }
//    /sendCurrentCoor();
  }
}

//char tempQ;
//void getCommand() {
//  while(xbee.available() <= 1 && command == STOP) { }
//  while(xbee.available() > 0) {
//    tempQ = xbee.read();
//    Serial.print(tempQ);
//    if(tempQ != ';')
//      commandQ.push(tempQ);
//    else
//      interpret();  
//  }
//}

int ii = 0;
int stringLen = 0;
bool firstTime = true;
char tempChar;
void getCommand(){
  while(xbee.available() <= 1 && command == STOP) { }
  while(xbee.available() > 0) {
    tempChar = xbee.read();
    if (firstTime == true){
      firstTime = false;  
    }
    else if(tempChar == '$'){
      stringLen = ii;
      ii = 0;
      command = START;
      interpret();
      //currCString[0] = '\0';
    }
    else if(tempChar == 's') {
      command = STOP;
    }
    //Serial.println(ii);
    currCString[ii] = tempChar;
    //Serial.println();
    ii++;
  }
}

void sendCurrentCoor() {
  xbee.print(gMap.pac->x1);
  xbee.print(" ");
  xbee.print(gMap.pac->x2);
  xbee.print(" ");
  xbee.print(gMap.pac->y1);
  xbee.print(" ");
  xbee.print(gMap.pac->y1);
  xbee.println();
}

//void interpret() {
//  char c;
//  while(commandQ.size > 0) {
//    c = commandQ.pop();
//    if(c == 0) {
////      command = START;
////      reset();
//    }
//    else if(c == 1) {
////      command = STOP;
////      logic.mode = DEAD;
//      driver.Kill();
//    }
//
//  }
//  commandQ.reset();
//}

int timer = 0, pos, prevPos = 1;
char delim = '#';
String token;

#define blinky (&gMap.ghosts[0].pos)
#define pinky (&gMap.ghosts[1].pos)
#define clyde (&gMap.ghosts[2].pos)
#define inky (&gMap.ghosts[3].pos)

void interpret(){
  String currString(currCString);
  //Serial.println(currString);
  //Serial.println(currCString);
  pos = 0; prevPos = 1;
  timer = 0;
  if(stringLen == 0){
    return;
  }
  if (stringLen < 4){ 
    command = STOP;
    return; 
  }
  //erase first char
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  gMap.pac->x = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  gMap.pac->y = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  blinky->x = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  blinky->y = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  pinky->x = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  pinky->y = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  clyde->x = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  clyde->y = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  inky->x = atoi(token.c_str());
  prevPos = pos+1;
  pos = currString.indexOf(delim, prevPos);
  token = currString.substring(prevPos, pos);
  inky->y = atoi(token.c_str());
  prevPos = pos+1;
  if (pos != stringLen){
    pos = currString.indexOf(delim, prevPos);
    token = currString.substring(prevPos, pos);
    timer = atoi(token.c_str());  
  }
// gMap.pac->printd();
//  blinky->printd();
//  pinky->printd();
//  clyde->printd();
//  inky->printd();
//  Serial.println(timer);
//   Serial.println(command == START);
    
}

void reset() {
  gMap.init(14, 14, 23, 24, UP);
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
