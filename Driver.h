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
#define ADJUSTMOTORS 22


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
		cRightSpeed = 0;
		cLeftSpeed = 0;
	}
	int calibWait = 20;
	void calibrate() {
		double ch = gyro->getChange();
		if(abs(ch) > 5 && calibWait < 0) {
			//Serial.println("Orientation:");
			//Serial.println(gyro->getOrientation());
			//Serial.println("Change:");
			//Serial.println(gyro->getChange());
			
			if(ch > 0) {
				if(cLeftSpeed > 0)
					cLeftSpeed--;
			}
			else { 
				if(cRightSpeed > 0)
					cRightSpeed--;
			}
			gyro->reset();
			calibWait = 20;
		}
		else {
			//Serial.println("Left:");
			//Serial.println(cLeftSpeed);
			//Serial.println("Right:");
			//Serial.println(cRightSpeed);
		}
		calibWait--;

	}

	void setStraight() {
		stop();
		status = MOVINGFORWARD;

	}

	volatile int adjustPeriod = 20;

	void moveForward() {
		if(cRightSpeed < TARGETSPEED && cLeftSpeed < TARGETSPEED && adjustPeriod < 0) {
			cRightSpeed++;
			cLeftSpeed++;
			adjustPeriod = 20;
		}
		adjustPeriod--;
		leftMotor->setDirection(CLOCKWISE);
		rightMotor->setDirection(CLOCKWISE);
		leftMotor->setSpeed(cLeftSpeed);
		rightMotor->setSpeed(cRightSpeed);
		leftMotor->move();
		rightMotor->move();
		
		calibrate();

		if(fronts->getDistance() < 8) {
			freeze();
			status = TURNINGRIGHT;
		}

	}

	void turnRight() {

	}

	void turnLeft() {

	}

	void turnBack() {

	}

	void turnAround() {

	}

	void stop() {
		leftMotor->stop();
		rightMotor->stop();
	}

	void freeze() {
		leftMotor->freeze();
		rightMotor->freeze();
		status = SLEEP;
	}

	void update(unsigned long dt) {
		move();

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

			case SLEEP:
			if(fronts->getDistance() > 8) {
				setAdjustState();
			}
			break;
			default:
			//
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
	int cRightSpeed = 80;
	int cLeftSpeed = 72;
	int TARGETSPEED = 250;
};

#endif
