#ifndef SENSOR
#define SENSOR

#define IR 0
#define IRSHORTL 3
#define IRSHORTR 4
#define US 1
#define IRD 2
#define CHAINSIZE 5

#define COVERED 0
#define OPEN 1

#include "Arduino.h"

class Sensor {
public:
	Sensor(short p, char ty) {
		pin = p;
		type = ty;
	}

	void init() {
		pinMode(pin, INPUT);
	}

	void update(unsigned long ts) {
		if(type == IRD) {
			val = digitalRead(pin);
		}
		else if(type == IRSHORTL) {
			val = analogRead(pin);
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
			chain[CHAINSIZE - 1] = (1205.254/(val + 80.154) + -1.403) / 5.0;
			timeChain[CHAINSIZE - 1] = (ts - timeStamp) / 1000.0;
			distance += chain[4];
			speedChain[CHAINSIZE - 1] = (chain[CHAINSIZE - 1] - chain[0]) / (timeAvg);
			spd += speedChain[CHAINSIZE - 1] / 5.0;
		}
		else if(type == IRSHORTR) {
			val = analogRead(pin);
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
			chain[CHAINSIZE - 1] = (2222.4745/(val + 244.088) + -1.7941) / 5.0;
			timeChain[CHAINSIZE - 1] = (ts - timeStamp) / 1000.0;
			distance += chain[4];
			speedChain[CHAINSIZE - 1] = (chain[CHAINSIZE - 1] - chain[0]) / (timeAvg);
			spd += speedChain[CHAINSIZE - 1] / 5.0;
		}
		else if(type == IR) {
			val = analogRead(pin);
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
			//Serial.println(distance);
			//Serial.print("\t");
			//Serial.println(spd);
		}
		timeStamp = ts;		
	}

	double speed() {
		return spd;
	}

	int getState() {
		return val;
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