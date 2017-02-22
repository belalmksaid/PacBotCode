#ifndef MOTOR
#define MOTOR

#define MAXSPEED 255
#define MINSPEED 0
#define CLOCKWISE 1
#define ANTICLOCKWISE -1
#define EPSILON 1.0

#include "Arduino.h"

class Motor {
public:
	Motor(int p1, int p2) {
		pin1 = p1;
		pin2 = p2;
	}

	void setSpeed(int s) {
		speed = min(s, MAXSPEED);
		speed = max(speed, MINSPEED);
	}

	void incrementSpeed(int a) {
		speed += a;
		speed = min(speed, MAXSPEED);
		speed = max(speed, MINSPEED);
	}

	void setDirection(char d) {
		direction = d;
	}

	void flipDirection() {
		direction = -direction;
	}

	int* getSpeedPointer() {
		return &speed;
	}

	char getDirection() {
		return direction;
	}

	void move() {
		if(direction == CLOCKWISE)
			analogWrite(pin1, speed);
		else {
			analogWrite(pin2, speed);
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
	int speed = 0;
	char direction = CLOCKWISE;
};

#endif