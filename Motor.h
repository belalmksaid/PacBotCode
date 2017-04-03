#ifndef MOTOR
#define MOTOR

#define MAXSPEED 255
#define MINSPEED 0
#define CLOCKWISE 1
#define ANTICLOCKWISE -1
#define EPSILON 1.0
#define CSTEPS 600
#define CONVERSION 0.00824565001

#include "Arduino.h"
#include "Encoder.h"

class Motor {
public:
	double speed = 0.0;
	double distance = 0.0;
	long encoderPos1 = 0;

	Motor(int p1, int p2, int a1, int a2) {
		pin1 = p1;
		pin2 = p2;
		enc = new Encoder(a1, a2);
	}

	void setValue(int s) {
		value = min(s, MAXSPEED);
		value = max(value, MINSPEED);
	}

	void incrementValue(int a) {
		value += a;
		value = min(value, MAXSPEED);
		value = max(value, MINSPEED);
	}

	void setDirection(char d) {
		direction = d;
	}

	void flipDirection() {
		direction = -direction;
	}

	char getDirection() {
		return direction;
	}

	void updateEncoder(unsigned long nframe) {
		if(enc->read() != encoderPos1) {
			encoderPos0 = encoderPos1;
			encoderPos1 = enc->read();
			distance = (encoderPos1 - encoderPos0) * CONVERSION;
			speed = distance / ((nframe - lastTime) / 1000000.0);
			lastTime = nframe;
			//Serial.println(speed);
		}
	}

	void move() {
		if(direction == CLOCKWISE) {
			analogWrite(pin1, value);
		}
		else {
			analogWrite(pin2, value);
		}
	}

	void stop() {
		analogWrite(pin1, 0);
		analogWrite(pin2, 0);
	}

	void freeze() {
		analogWrite(pin1, 255);
		analogWrite(pin2, 255);
	}


private:
	int pin1 = 0;
	int pin2 = 0;
	int value = 0;
	char direction = CLOCKWISE;
	Encoder* enc;
	long encoderPos0 = 0;
	unsigned long newTime = 0;
	unsigned long lastTime = 0;
};

#endif