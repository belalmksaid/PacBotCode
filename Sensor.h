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

#define ceiling 4.1 // maximum distance by the Sensor

#include "Arduino.h"

class Sensor {
public:
	double distance = 0.0;
	double speed = 0.0;
	
	Sensor(short p, char ty) {
		pin = p;
		type = ty;
	}

	void init() {
		pinMode(pin, INPUT);
	}

	void resetChain() {
		for(int i = 0; i < CHAINSIZE; i++) {
			chain[i] = 0;
			speedChain[i] = 0.0;
		}
	}

	double p = 0, p2 = 0;

	void update(unsigned long ts) {
		if(type == IRD) {
			val = digitalRead(pin);
		}
		else if(type == IRSHORTL) {
			if(ts - timeStamp < 20000)
				return;
			val = analogRead(pin);
			p = (454.1513/(val + -52.5) + -1.059);
			p = p + (0.7) * (oldDistance - p);
			if((abs(p) > 4 || p < -0.3) || (abs(oldDistance) > 4 || oldDistance < -0.3)) {
				distance = 0;
			}
			else { 
				distance = p;
			}
			oldDistance = p;
			timeStamp = ts;				
		}
		else if(type == IRSHORTR) {
			if(ts - timeStamp < 20000)
				return;
			val = analogRead(pin);
			p = 505.72/(val - 45.76) + -1.104;
			p = p + (0.7) * (oldDistance - p);
			if((abs(p) > 4 || p < -0.3) || (abs(oldDistance) > 4 || oldDistance < -0.3)) {
				distance = 0;
			}
			else { 
				distance = p;
			}
			oldDistance = p;
			timeStamp = ts;
		}
		else if(type == IR) {
			if(ts - timeStamp < 20000)
				return;
			val = analogRead(pin);
			p = (4406.752818/(val + 51.80904) + -1.74687);
			p = p + (0.7) * (oldDistance - p);
			distance = p;
			oldDistance = p;
			//Serial.println(distance);
		}		
	}
	int getState() {
		return val;
	}

private:
	short pin;
	char type;
	int val;
	double chain[CHAINSIZE] = {-10000000, -10000000, -100000000, -1000000000,- 1000000000};
	double timeChain[CHAINSIZE] = {0, 0, 0, 0, 0};
	double oldDistance = 0.0;
	double speedChain[CHAINSIZE] = {-100000, -100000, -100000, -100000, -100000};
	unsigned long timeStamp = 0;
	double timeAvg = 0.0;
};

#endif