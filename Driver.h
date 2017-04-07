#ifndef DRIVER
#define DRIVER

#define TURNINGRIGHT 1
#define TURNINGLEFT 10
#define TURNINGBACK 4
#define FROZEN 0
#define MOVINGFORWARD 2
#define MOVINGBACKWARD 20
#define SLEEP 18
#define ADJUSTMOTORS 22

#define FORWARDSPEED 12.0
#define TURNINGSPEED 8.0

#define COOLDOWN() delay(150)


#include "Motor.h"
#include "Sensor.h"
//#include "GyroAccl.h"
#include "Arduino.h"
#include "PID_v1.h"


#define BD 3.723475
#define WD 1.5575
#define STEPS90 BD * PI / 4.0 / (WD * PI) * CSTEPS - 27
#define STEPS180 (STEPS90 + 1.0) * 2.0


class Driver {
public:
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
	Sensor* rightD, *leftD;
	//GyroAccl* gyro;
	double leftPWM = 75;
	double rightMasterPWM = 60;
	double desiredSpeed = 12.0;
	double dummyRight = 0.0, dummyLeft = 0.0;
	double speedAdjust = 0.0;
	unsigned long dt = 0;
	PID* pid; 
	PID* pidWall;
	PID* pidspeed;
	PID* pidturnR, *pidturnL;
	double d = 0.0;

	Driver(Motor* left, Motor* right, Sensor* a, Sensor* b, Sensor* c, Sensor* dd, Sensor* rd, Sensor* ld) {
		leftMotor = left;
		rightMotor = right;
		fronts = a;
		backs = b;
		rights = c;
		lefts = dd;
		rightD = rd;
		leftD = ld;
		pid = new PID(&dummyLeft, &leftPWM, &dummyRight, 0.005, 50, 0.05, DIRECT);
		pidspeed = new PID(&rightMotor->speed, &rightMasterPWM, &desiredSpeed, 2, 0.5, 0, DIRECT);
		pidturnL = new PID(&dummyLeft, &leftPWM, &desiredSpeed, .01, 25, .05, DIRECT);
		pidturnR =  new PID(&dummyRight, &rightMasterPWM, &desiredSpeed, .01, 25, .05, DIRECT);
		pidWall = new PID(&rights->speed, &speedAdjust, &d, 1, 0, 0.2, REVERSE);
	}

	void init() {
		fronts->init();
		lefts->init();
		pid->SetMode(AUTOMATIC);
		pidspeed->SetMode(AUTOMATIC);
		pidspeed->SetOutputLimits(0, 230);
		pidturnR->SetMode(AUTOMATIC);
		pidturnL->SetMode(AUTOMATIC);
		pidWall->SetMode(AUTOMATIC);
		pidWall->SetSampleTime(50);
		pidWall->SetOutputLimits(-50, 50);
	}

	void setAdjust() {
		stop();
		status = ADJUSTMOTORS;
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
		desiredSpeed = TURNINGSPEED;
	}

	void setLeft() {
		if(status == TURNINGLEFT) return;
		freeze();
		status = TURNINGLEFT;
		desiredSpeed = TURNINGSPEED;
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
	}

	void update(unsigned long d) {
		dt = d;
		dummyLeft = abs(leftMotor->speed);
		dummyRight = abs(rightMotor->speed);
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
			case ADJUSTMOTORS:
			adjust();
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
	double var = 0.0;
	volatile long startEncLeft = 0;
	volatile long startEncRight = 0;
	void turnRight() {
		if(fcall) {
			stop();
			fcall = false;
			startEncRight = rightMotor->encoderPos1;
			startEncLeft = leftMotor->encoderPos1;
			pidturnR->Reset();
			pidturnL->Reset();
		}
		else {
			if(startEncLeft + STEPS90 <= leftMotor->encoderPos1 && startEncRight - rightMotor->encoderPos1 >= STEPS90) {
				fcall = true;
				freeze();
				COOLDOWN();
				return;
			}
			
			if(startEncLeft + STEPS90 <= leftMotor->encoderPos1) {
				leftMotor->freeze();
			}
			else {
				leftMotor->setDirection(ANTICLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				leftMotor->move();
				dummyLeft = abs(leftMotor->speed);
				pidturnL->Compute();
			}
			if(startEncRight - rightMotor->encoderPos1 >= STEPS90) {
				rightMotor->freeze();
			}
			else {
				rightMotor->setDirection(ANTICLOCKWISE);
				rightMotor->setValue((int)rightMasterPWM);
				rightMotor->move();
				dummyRight = abs(rightMotor->speed);
				pidturnR->Compute();
			}

			Serial.println(STEPS90);
		}
	}

	void turnLeft() {
		if(fcall) {
			stop();
			fcall = false;
			startEncRight = rightMotor->encoderPos1;
			startEncLeft = leftMotor->encoderPos1;
			pidturnR->Reset();
			pidturnL->Reset();
		}
		else {
			if(startEncLeft - leftMotor->encoderPos1 >= STEPS90 && startEncRight + STEPS90 <= rightMotor->encoderPos1) {
				fcall = true;
				freeze();
				COOLDOWN();
			}
			else {
				leftMotor->setDirection(CLOCKWISE);
				rightMotor->setDirection(CLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				rightMotor->setValue((int)rightMasterPWM);
				leftMotor->move();
				rightMotor->move();
				pidturnL->Compute();
				pidturnR->Compute();
			}
		}

	}

	void turnAroundCW() {

	}

	void turnAroundCCW() {

	}

	void adjust() {
		if(fcall) {
			stop();
			fcall = false;
			startEncRight = rightMotor->encoderPos1;
			startEncLeft = leftMotor->encoderPos1;
			pidturnR->Reset();
			pidturnL->Reset();
		}
		else {
			if(startEncLeft - 585 >= leftMotor->encoderPos1 && startEncRight + 580 <= rightMotor->encoderPos1) {
				fcall = true;
				freeze();
				COOLDOWN();
			}
			else {
				leftMotor->setDirection(CLOCKWISE);
				rightMotor->setDirection(CLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				rightMotor->setValue((int)rightMasterPWM);
				leftMotor->move();
				rightMotor->move();
				dummyLeft = abs(leftMotor->speed);
				dummyRight = abs(rightMotor->speed);
				pidturnL->Compute();
				pidturnR->Compute();
			}
		}

	}

	void moveForward() {
		//calibrate2(dt);
		leftMotor->setDirection(ANTICLOCKWISE);
		rightMotor->setDirection(CLOCKWISE);
		leftMotor->setValue((int)leftPWM);
		rightMotor->setValue((int)rightMasterPWM);
		leftMotor->move();
		rightMotor->move();
		pid->Compute();
		#ifdef ASERIAL
			Serial.print(leftMotor->speed);
			Serial.print("\t");
			Serial.print(rightMotor->speed);
			Serial.println();
		#endif
		pidspeed->Compute();
	}

	void calibrate() {
		if(rightD->getState() == COVERED && leftD->getState() == COVERED) {
			pidWall->Compute();
			//#ifdef ASERIAL
			Serial.print(lefts->distance);
			Serial.print("\t");
			Serial.print(lefts->speed);
			Serial.print("\t");
			Serial.print(rights->distance);
			Serial.print("\t");
			Serial.println(rights->speed);
			//Serial.print("\t");
			//#endif
			//Serial.println(speedAdjust);
			dummyLeft -= speedAdjust;
			dummyRight += speedAdjust;
			//#ifdef ASERIAL
			//#endif
		}
	}
	long prev = 0;
	long prevTime = 0;
	bool fvall = true;
	int updateTime = 200000;
	void calibrate2(unsigned long time) {
		if(lefts->speed > 0.05) {
			if(fvall) {
				prev = leftMotor->encoderPos1;
				fvall = false;
				prevTime = time;
			}
			else {
				if(time - prevTime < updateTime) return; 
				double distance = (leftMotor->encoderPos1 - prev) / 590.0 * 1.575 * 3.141593;
				double dt = (time - prevTime)/ 1000000.0;
				prev = leftMotor->encoderPos1;
				prevTime = time;
				double at = atan2(lefts->speed, distance) * 2.0 / dt ;
				dummyLeft += at;
			}

		}
		if(lefts->speed < -0.05) {
			if(fvall) {
				prev = leftMotor->encoderPos1;
				fvall = false;
				prevTime = time;
			}
			else {
				if(time - prevTime < updateTime) return; 
				double distance = (leftMotor->encoderPos1 - prev) / 590.0 * 1.575 * 3.141593;
				double dt = (time - prevTime)/ 1000000.0;
				prev = leftMotor->encoderPos1;
				prevTime = time;
				double at = atan2(-1*lefts->speed, distance) * 2.0 / dt ;
				dummyLeft -= at;
			}

		}
		// else if(rights->speed > 0.05) {
		// 	if(fvall) {
		// 		prev = rightMotor->encoderPos1;
		// 		fvall = false;
		// 		prevTime = time;
		// 	}
		// 	else {
		// 		if(time - prevTime < 75000) return; 
		// 		double distance = (rightMotor->encoderPos1 - prev) / 640.0 * 1.575 * 3.141593;
		// 		double dt = (time - prevTime)/ 1000000.0;
		// 		prev = rightMotor->encoderPos1;
		// 		prevTime = time;
		// 		double at = atan2(rights->speed, distance) * 2.0 / dt ;
		// 		dummyLeft -= at;
		// 	}

		// }
	}
};

#endif
