#ifndef SENSOR
#define SENSOR

#define IR 0
#define US 1
#define IRD 2
#define CHAINSIZE 5

#include "Arduino.h"

class Sensor {
public:
	Sensor(short p, char ty, unsigned long* d) {
		pin = p;
		type = ty;
		dt = d;
	}

	void init() {
		pinMode(pin, OUTPUT);
	}

	void update() {
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

			/*d1 = d2;
			d2 = distance();
			spd = 0.0;
			if(abs(d2 - d1) > 0.1) { 
				spd = abs(d2 - d1) / (*dt / 1000.0);
			}*/
		}		
	}

	double speed() {
		return spd;
	}

	double distance() {
		if(type != IRD) {
			return chain[0] + chain[1] + chain[2] + chain[3] + chain[4];
		}
		return val;
	}
private:
	short pin;
	char type;
	int val;
	double chain[CHAINSIZE] = {-10000000, -10000000, -100000000, -1000000000,- 1000000000};
	double speedChain[CHAINSIZE] = {-100000, -100000, -100000, -100000, -100000};
	double d1 = 0;
	double d2 = 0;
	unsigned long* dt;
	double spd = 0.0;
};

#endif