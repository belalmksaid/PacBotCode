#ifndef SENSOR
#define SENSOR

#define IR 0
#define US 1
#define IRD 2
#define CHAINSIZE 5

#include "Arduino.h"

class Sensor {
public:
	Sensor(short p, char ty) {
		pin = p;
		type = ty;
	}

	void init() {
		pinMode(pin, OUTPUT);
	}

	void update(unsigned long ts) {
		val = analogRead(pin);
		if(type == IRD) {
			val = val < 500 ? 0 : 1;
		}
		else {
			chain[0] = chain[1];
			chain[1] = chain[2];
			chain[2] = chain[3];
			chain[3] = chain[4];
			chain[4] = (4406.752818/(val + 51.80904) + -1.74687) / 5.0;
			distance = chain[0] + chain[1] + chain[2] + chain[3] + chain[4];
		}
		timeStamp = ts;		
	}

	double speed() {
		return spd;
	}

	double getDistance() {
		if(type != IRD) {
			return distance;
		}
		return val;
	}
private:
	short pin;
	char type;
	int val;
	double chain[CHAINSIZE] = {-10000000, -10000000, -100000000, -1000000000,- 1000000000};
	double distance = 0.0;
	double speedChain[CHAINSIZE] = {-100000, -100000, -100000, -100000, -100000};
	double spd = 0.0;
	unsigned long timeStamp = 0;
};

#endif