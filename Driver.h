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

#define SPEEDCAP 255
#define IDEAL 150


#include "Motor.h"
#include "Sensor.h"
#include "GyroAccl.h"
#include "Arduino.h"

class Driver {
public:
	Driver(Motor* left, Motor* right, Sensor* a, Sensor* b, Sensor* c, Sensor* dd, GyroAccl* g) {
		leftMotor = left;
		rightMotor = right;
		gyro = g;
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
		double ch = 0.0 - gyro->getChange();
		double time = (double)dt;

		errsum += ch;
		double derr = (ch - error) / time;

		double res = kp * ch + ki * errsum + kd * derr;

		error = ch;

		if(res < 0.0) {
			if(cRightSpeed < IDEAL) {
				cRightSpeed += (int) abs(res);
			}
			else {
				cLeftSpeed -= (int) abs(res);
			}
		}
		else {
			if(cLeftSpeed < IDEAL) {
				cLeftSpeed += (int) abs(res);
			}
			else {
				cRightSpeed -= (int) abs(res);
			}
		}

		if(cRightSpeed > IDEAL) {
			cRightSpeed -= (IDEAL - cRightSpeed);
			cLeftSpeed -= (IDEAL - cRightSpeed);
		}
		else if(cLeftSpeed > IDEAL) {
			cRightSpeed -= (IDEAL - cLeftSpeed);
			cLeftSpeed -= (IDEAL - cLeftSpeed);
		}

		Serial.println(res);
		gyro->reset();

	}

	void setStraight() {
		status = MOVINGFORWARD;
		Serial.println(status == MOVINGFORWARD);
	}

	void moveForward() {
		if(fcall) {
			fcall = false;
		}
		leftMotor->setDirection(CLOCKWISE);
		rightMotor->setDirection(CLOCKWISE);
		leftMotor->setSpeed(cRightSpeed);
		rightMotor->setSpeed(cLeftSpeed);
		leftMotor->move();
		rightMotor->move();
		
		calibrate();

		/*if(fronts->getDistance() < 8) {
			freeze();
		}*/
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

	void update(unsigned long d) {
		dt = d;
		if(dt == 0) dt = 1; 
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
	Sensor* fronts;
	Sensor* backs;
	Sensor* lefts;
	Sensor* rights;
	GyroAccl* gyro;
	int cRightSpeed = 40;
	int cLeftSpeed = 40;
	unsigned long dt = 0;
	double error = 0.0, errsum = 0.0;
	double kp = 1.0, ki = 1.0, kd = 1.0;
};

#endif