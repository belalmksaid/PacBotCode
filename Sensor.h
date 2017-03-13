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
			if(ts - timeStamp < 100)
				return;
			oldDistance = distance;
			distance = 0.0;
			timeAvg = 0.0;
			spd = 0.0;
			for(int i = 0; i < CHAINSIZE - 1; i++) {
    			chain[i] = chain[i + 1];
    			timeChain[i] = timeChain[i + 1];
    			timeAvg += timeChain[i + 1];
    			speedChain[i] = speedChain[i + 1];
    			distance += chain[i + 1];
    			spd += speedChain[i + 1];
    		}
			chain[CHAINSIZE - 1] = (4406.752818/(val + 51.80904) + -1.74687) / 5.0;
			timeChain[CHAINSIZE - 1] = (ts - timeStamp) / 1000.0;
			distance += chain[4];
			speedChain[CHAINSIZE - 1] = (chain[CHAINSIZE - 1] - chain[0]) / (timeAvg);
			spd += speedChain[CHAINSIZE - 1] / 5.0;
			Serial.print(distance);
			Serial.print("\t");
			Serial.println(spd);
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
	double timeChain[CHAINSIZE] = {0, 0, 0, 0, 0};
	double distance = 0.0;
	double oldDistance = 0.0;
	double speedChain[CHAINSIZE] = {-100000, -100000, -100000, -100000, -100000};
	double spd = 0.0;
	unsigned long timeStamp = 0;
	double timeAvg = 0.0;
};

#endif