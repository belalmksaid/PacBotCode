#ifndef DRIVER
#define DRIVER

#define TURNINGRIGHT 1
#define TURNINGLEFT 10
#define TURNINGBACKCW 4
#define TURNINGBACKCCW 9
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
#include "Arduino.h"
#include "PID_v1.h"


#define BD 3.723475
#define WD 1.5575
#define STEPS90 BD * PI / 4.0 / (WD * PI) * CSTEPS - 29
#define STEPS180 (STEPS90) * 2.0 + 25.0

#define thre 0.32


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
	double speedAdjust = 0.0, distanceAdjust = 0.0;
	unsigned long dt = 0;
	PID* pid; 
	PID* walld, *walls;
	PID* pidspeed;
	PID* pidturnR, *pidturnL;
	PID* hlwalld, *hlwalls;
	PID* hrwalld, *hrwalls;

	double ilength = 2.75; // ideal side distance
	double ispeed = 0.0; // ideal speed

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
		walld = new PID(&rights->distance, &distanceAdjust, &lefts->distance, 0.25, 2, 0.1, DIRECT); //1,0,.2
		walls = new PID(&rights->speed, &speedAdjust, &lefts->speed, 2, 0, 0.5, DIRECT); //1,0,0
		hlwalld = new PID(&lefts->distance, &distanceAdjust, &ilength, 0.25, 2, 0.1, DIRECT); //1,0,.2
		hlwalls = new PID(&lefts->speed, &speedAdjust, &ispeed, 2, 0, 0.5, DIRECT); //1,0,0
		hrwalld = new PID(&rights->distance, &distanceAdjust, &ilength, 0.25, 2, 0.1, DIRECT); //1,0,.2
		hrwalls = new PID(&rights->speed, &speedAdjust, &ispeed, 2, 0, 0.5, DIRECT); //1,0,0
	}

	void init() {
		fronts->init();
		lefts->init();
		pid->SetMode(AUTOMATIC);
		pidspeed->SetMode(AUTOMATIC);
		pidspeed->SetOutputLimits(0, 230);
		pidturnR->SetMode(AUTOMATIC);
		pidturnL->SetMode(AUTOMATIC);
		walld->SetMode(AUTOMATIC);
		walld->SetSampleTime(75);
		walld->SetOutputLimits(-6, 6);
		walls->SetMode(AUTOMATIC);
		walls->SetSampleTime(75);
		walls->SetOutputLimits(-6, 6);
		hlwalld->SetMode(AUTOMATIC);
		hlwalld->SetSampleTime(75);
		hlwalld->SetOutputLimits(-6, 6);
		hlwalls->SetMode(AUTOMATIC);
		hlwalls->SetSampleTime(75);
		hlwalls->SetOutputLimits(-6, 6);
		hrwalld->SetMode(AUTOMATIC);
		hrwalld->SetSampleTime(75);
		hrwalld->SetOutputLimits(-6, 6);
		hrwalls->SetMode(AUTOMATIC);
		hrwalls->SetSampleTime(75);
		hrwalls->SetOutputLimits(-6, 6);
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
		fcall = true;
	}

	void setRight() {
		if(status == TURNINGRIGHT) return;
		freeze();
		status = TURNINGRIGHT;
		desiredSpeed = TURNINGSPEED;
		fcall = true;
	}

	void setLeft() {
		if(status == TURNINGLEFT) return;
		freeze();
		status = TURNINGLEFT;
		desiredSpeed = TURNINGSPEED;
		fcall = true;
	}

	void setCCW() {
		if(status == TURNINGBACKCCW) return;
		freeze();
		status = TURNINGBACKCCW;
		desiredSpeed = TURNINGSPEED;
		fcall = true;
	}

	void setCW() {
		if(status == TURNINGBACKCW) return;
		freeze();
		status = TURNINGBACKCW;
		desiredSpeed = TURNINGSPEED;
		fcall = true;
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
			break;
			case TURNINGBACKCW:
			turnAroundCW();
			break;
			case TURNINGBACKCCW:
			turnAroundCCW();
			break;
			case SLEEP:
			break;
			default:
			//
			break;
		}
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
				freeze();
				COOLDOWN();
				return;
			}

			if(startEncLeft - leftMotor->encoderPos1 >= STEPS90) {
				leftMotor->freeze();
			}
			else {
				leftMotor->setDirection(CLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				leftMotor->move();
				dummyLeft = abs(leftMotor->speed);
				pidturnL->Compute();
			}
			if(startEncRight + STEPS90 <= rightMotor->encoderPos1) {
				rightMotor->freeze();
			}
			else {
				rightMotor->setDirection(CLOCKWISE);
				rightMotor->setValue((int)rightMasterPWM);
				rightMotor->move();
				dummyRight = abs(rightMotor->speed);
				pidturnR->Compute();
			}
		}

	}

	void turnAroundCW() {
		if(fcall) {
			stop();
			fcall = false;
			startEncRight = rightMotor->encoderPos1;
			startEncLeft = leftMotor->encoderPos1;
			pidturnR->Reset();
			pidturnL->Reset();
		}
		else {
			if(startEncLeft + STEPS180 <= leftMotor->encoderPos1 && startEncRight - rightMotor->encoderPos1 >= STEPS180) {
				freeze();
				COOLDOWN();
				return;
			}
			
			if(startEncLeft + STEPS180 <= leftMotor->encoderPos1) {
				leftMotor->freeze();
			}
			else {
				leftMotor->setDirection(ANTICLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				leftMotor->move();
				dummyLeft = abs(leftMotor->speed);
				pidturnL->Compute();
			}
			if(startEncRight - rightMotor->encoderPos1 >= STEPS180) {
				rightMotor->freeze();
			}
			else {
				rightMotor->setDirection(ANTICLOCKWISE);
				rightMotor->setValue((int)rightMasterPWM);
				rightMotor->move();
				dummyRight = abs(rightMotor->speed);
				pidturnR->Compute();
			}
		}
	}

	void turnAroundCCW() {
		if(fcall) {
			stop();
			fcall = false;
			startEncRight = rightMotor->encoderPos1;
			startEncLeft = leftMotor->encoderPos1;
			pidturnR->Reset();
			pidturnL->Reset();
		}
		else {
			if(startEncLeft - leftMotor->encoderPos1 >= STEPS180 && startEncRight + STEPS180 <= rightMotor->encoderPos1) {
				freeze();
				COOLDOWN();
			}

			if(startEncLeft - leftMotor->encoderPos1 >= STEPS180) {
				leftMotor->freeze();
			}
			else {
				leftMotor->setDirection(CLOCKWISE);
				leftMotor->setValue((int)leftPWM);
				leftMotor->move();
				dummyLeft = abs(leftMotor->speed);
				pidturnL->Compute();
			}
			if(startEncRight + STEPS180 <= rightMotor->encoderPos1) {
				rightMotor->freeze();
			}
			else {
				rightMotor->setDirection(CLOCKWISE);
				rightMotor->setValue((int)rightMasterPWM);
				rightMotor->move();
				dummyRight = abs(rightMotor->speed);
				pidturnR->Compute();
			}
		}
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
			leftMotor->setDirection(ANTICLOCKWISE);
			rightMotor->setDirection(CLOCKWISE);
			leftMotor->setValue((int)leftPWM);
			rightMotor->setValue((int)rightMasterPWM);
			// leftMotor->move();
			// rightMotor->move();
			walld->Compute();
			walls->Compute();
			double v = (distanceAdjust + speedAdjust) > thre ? (distanceAdjust + speedAdjust) - thre : (distanceAdjust + speedAdjust) < -thre ? (distanceAdjust + speedAdjust) + thre : 0;
			dummyLeft += v / 3.0;
			pid->Compute();
			pidspeed->Compute();
			Serial.print(lefts->distance);
			Serial.print("\t");
			// Serial.print(lefts->speed);
			// Serial.print("\t");
			Serial.println(rights->distance);
			// Serial.println("\t");
			Serial.println(v);
			// Serial.print("\t");
			// Serial.println(distanceAdjust);
			// Serial.print(leftMotor->speed);
			// Serial.print("\t");
			// Serial.print(rightMotor->speed);
			// Serial.println("\t");
			// Serial.println(distanceAdjust);
			// double thre = 0.32;
			// double v = (distanceAdjust - speedAdjust) > thre ? (distanceAdjust - speedAdjust) - thre : (distanceAdjust - speedAdjust) < -thre ? (distanceAdjust - speedAdjust) + thre : 0;
			// Serial.println(v / 3.0);
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
		calibrate();
		pid->Compute();
		pidspeed->Compute();
		#ifdef ASERIAL
			Serial.print(leftMotor->speed);
			Serial.print("\t");
			Serial.print(rightMotor->speed);
			Serial.println();
		#endif
	}

	void calibrate() {
		if(lefts->distance == 0.0 && rights->distance > 0.0 && rights->distance <= 2.0) {
			walls->Reset();
			walld->Reset();
			hlwalls->Reset();
			hlwalls->Reset();
			hrwalls->Compute();
			hrwalld->Compute();
			dummyLeft += ((distanceAdjust + speedAdjust) > thre ? (distanceAdjust + speedAdjust) - thre : (distanceAdjust + speedAdjust) < -thre ? (distanceAdjust + speedAdjust) + thre : 0) / 6.0;
		}
		else if(rights->distance == 0.0 && lefts->distance > 0.0 && lefts->distance <= 2.0) {
			walls->Reset();
			walld->Reset();
			hrwalls->Reset();
			hrwalls->Reset();
			hlwalls->Compute();
			hlwalld->Compute();
			dummyLeft += ((distanceAdjust + speedAdjust) > thre ? (distanceAdjust + speedAdjust) - thre : (distanceAdjust + speedAdjust) < -thre ? (distanceAdjust + speedAdjust) + thre : 0) / 6.0;
		}
		else if(lefts->distance >= 0.5 && rights->distance >= 0.5 && (lefts->distance <= 2 || rights->distance <= 2)) {
			hlwalls->Reset();
			hlwalls->Reset();
			hrwalls->Reset();
			hrwalls->Reset();
			walld->Compute();
			walls->Compute();
			dummyLeft += ((distanceAdjust + speedAdjust) > thre ? (distanceAdjust + speedAdjust) - thre : (distanceAdjust + speedAdjust) < -thre ? (distanceAdjust + speedAdjust) + thre : 0) / 3.0;
			//Serial.println( ((distanceAdjust + speedAdjust) > thre ? (distanceAdjust + speedAdjust) - thre : (distanceAdjust + speedAdjust) < -thre ? (distanceAdjust + speedAdjust) + thre : 0) / 3.0);
		}
		else {
			// Serial.print(lefts->distance);
			// Serial.print("\t");
			// // Serial.print(lefts->speed);
			// // Serial.print("\t");
			// Serial.print(rights->distance);
			// Serial.println("\t");
			walls->Reset();
			walld->Reset();
			hlwalls->Reset();
			hlwalls->Reset();
			hrwalls->Reset();
			hrwalls->Reset();
		}
	}
	// long prev = 0;
	// long prevTime = 0;
	// bool fvall = true;
	// int updateTime = 200000;
	// void calibrate2(unsigned long time) {
	// 	if(lefts->speed > 0.05) {
	// 		if(fvall) {
	// 			prev = leftMotor->encoderPos1;
	// 			fvall = false;
	// 			prevTime = time;
	// 		}
	// 		else {
	// 			if(time - prevTime < updateTime) return; 
	// 			double distance = (leftMotor->encoderPos1 - prev) / 590.0 * 1.575 * 3.141593;
	// 			double dt = (time - prevTime)/ 1000000.0;
	// 			prev = leftMotor->encoderPos1;
	// 			prevTime = time;
	// 			double at = atan2(lefts->speed, distance) * 2.0 / dt ;
	// 			dummyLeft += at;
	// 		}

	// 	}
	// 	if(lefts->speed < -0.05) {
	// 		if(fvall) {
	// 			prev = leftMotor->encoderPos1;
	// 			fvall = false;
	// 			prevTime = time;
	// 		}
	// 		else {
	// 			if(time - prevTime < updateTime) return; 
	// 			double distance = (leftMotor->encoderPos1 - prev) / 590.0 * 1.575 * 3.141593;
	// 			double dt = (time - prevTime)/ 1000000.0;
	// 			prev = leftMotor->encoderPos1;
	// 			prevTime = time;
	// 			double at = atan2(-1*lefts->speed, distance) * 2.0 / dt ;
	// 			dummyLeft -= at;
	// 		}

	// 	}
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
	// }
};

#endif
