#ifndef DRIVER
#define DRIVER

#define TURNINGRIGHT 1
#define TURNINGLEFT 10
#define TURNAROUND 5
#define TURNINGBACK 4
#define FROZEN 0
#define MOVINGFORWARD 2
#define MOVINGBACKWARD 20
#define SLEEP 18


#include "Motor.h"
#include "Sensor.h"
#include "Gyro.h"
#include "Arduino.h"

class Driver {
public:
	Driver(Motor* left, Motor* right, Sensor* a, Sensor* b, Sensor* c, Sensor* dd, Gyro* g, unsigned long* d) {
		leftMotor = left;
		rightMotor = right;
		gyro = g;
		dt = d;
		fronts = a;
		backs = b;
		rights = c;
		lefts = dd;
	}

	void init() {
		fronts->init();
		rights->init();
		gyro->init();
	}

	void calibrate() {

	}

	void setStraight() {
		status = MOVINGFORWARD;
		Serial.println(status == MOVINGFORWARD);
	}

	void moveForward() {
		if(fcall) {
			fcall = false;
		}
		leftMotor->setDirection(ANTICLOCKWISE);
		rightMotor->setDirection(ANTICLOCKWISE);
		leftMotor->setSpeed(cRightSpeed);
		rightMotor->setSpeed(cLeftSpeed);
		leftMotor->move();
		rightMotor->move();
		if(fronts->distance() < 8) {
			freeze();
		}
		calibrate();
	}

	void turnRight() {

	}

	void turnLeft() {

	}

	void turnBack() {

	}

	void turnAround() {

	}

	void freeze() {
		leftMotor->freeze();
		rightMotor->freeze();
		status = SLEEP;
	}

	void update() {
		fronts->update();
		rights->update();
		gyro->update();
	}

	void move() {
		switch(status) {
			case TURNINGRIGHT:
			turnRight();
			break;
			case TURNINGLEFT:
			turnLeft();
			break;
			case FROZEN:
			freeze();
			break;
			case MOVINGFORWARD:
			moveForward();
			break;
			default:
			calibrate();
			break;
		}
	}

	char getStatus() {
		return status;
	}
private:
	Motor* leftMotor;
	Motor* rightMotor;
	int cStep = 1000;
	char status = SLEEP;
	bool fcall = true;
	bool locked = false;
	unsigned long* dt;
	Sensor* fronts;
	Sensor* backs;
	Sensor* lefts;
	Sensor* rights;
	Gyro* gyro;
	int cRightSpeed = 40;
	int cLeftSpeed = 40;
};

#endif