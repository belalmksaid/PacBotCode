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

#define FORWARDSPEED 12.0
#define TURNINGSPEED 8.0


#include "Motor.h"
#include "Sensor.h"
//#include "GyroAccl.h"
#include "Arduino.h"
#include "PID_v1.h"

#define STEPS90 CSTEPS * 0.635 - 1.0
#define STEPS180 (STEPS90 + 1.0) * 2.0 - 1.0


class Driver {
public:
	Driver(Motor* left, Motor* right, Sensor* a, Sensor* b, Sensor* c, Sensor* dd) {
		leftMotor = left;
		rightMotor = right;
		//gyro = g;
		fronts = a;
		backs = b;
		rights = c;
		lefts = dd;
		pid = new PID(&leftMotor->speed, &leftPWM, &rightMotor->speed, 3, .5, 0.3, DIRECT);
		pidspeed = new PID(&rightMotor->speed, &rightMasterPWM, &desiredSpeed, 3, .5, .3, DIRECT);
		pidturn = new PID(&leftMotor->speed, &leftPWM, &antiTurningSpeed, 3, .5, .3, DIRECT);
	}

	void init() {
		fronts->init();
		lefts->init();
		pid->SetMode(AUTOMATIC);
		pid->SetControllerDirection(REVERSE);
		pidspeed->SetMode(AUTOMATIC);
		pidspeed->SetControllerDirection(REVERSE);
		pidspeed->SetOutputLimits(0, 230);
		pidturn->SetMode(AUTOMATIC);
		pidturn->SetControllerDirection(REVERSE);
		//gyro->init();
	}


	void setStraight() {
		if(status == MOVINGFORWARD) return;
		stop();
		status = MOVINGFORWARD;
		desiredSpeed = FORWARDSPEED;
	}

	void setRight() {
		if(status == TURNINGRIGHT) return;
		freeze();
		status = TURNINGRIGHT;
		desiredSpeed = -TURNINGSPEED;
		antiTurningSpeed = -desiredSpeed;
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

	void updateEncodersOnly(unsigned long d) {
		dt = d;
		leftMotor->updateEncoder(d);
		rightMotor->updateEncoder(d);
		/*Serial.print(leftMotor->speed);
		Serial.print("\t");
		Serial.print(rightMotor->speed);
		Serial.println();*/
	}

	void update() {
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
	volatile char status = SLEEP;
	bool fcall = true;
	bool locked = false;
	Sensor* fronts;
	Sensor* backs;
	Sensor* lefts;
	Sensor* rights;
	//GyroAccl* gyro;
	double leftPWM = 80;
	double rightMasterPWM = 60;
	double desiredSpeed = 12.0;
	double antiTurningSpeed = -8.0;
	unsigned long dt = 0;
	PID* pid; 
	//PID* pidwall;
	PID* pidspeed;
	PID* pidturn;

	double var = 0.0;

	long startEncLeft = 0;
	long startEncRight = 0;
	void turnRight() {
		if(fcall) {
			stop();
			fcall = false;
			startEncRight = rightMotor->encoderPos1;
			startEncLeft = leftMotor->encoderPos1;
			pidspeed->Reset();
			pidturn->Reset();
		}
		else {
			if(startEncLeft + STEPS90 <= leftMotor->encoderPos1) {
				fcall = true;
				freeze();
				setStraight();
			}
			else {
				leftMotor->setDirection(ANTICLOCKWISE);
				rightMotor->setDirection(ANTICLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				rightMotor->setValue((int)rightMasterPWM);
				leftMotor->move();
				rightMotor->move();
				pidspeed->Compute();
				pidturn->Compute();
			}
		}
	}

	void turnLeft() {

	}

	void turnBack() {

	}

	void turnAround() {

	}

	void moveForward() {
		leftMotor->setDirection(ANTICLOCKWISE);
		rightMotor->setDirection(CLOCKWISE);
		leftMotor->setValue((int)leftPWM);
		rightMotor->setValue((int)rightMasterPWM);
		leftMotor->move();
		rightMotor->move();
		pid->Compute();
		pidspeed->Compute();
		//calibrateF();

		if(fronts->getDistance() < 8) {
			//setRight();
		}

	}
};

#endif
