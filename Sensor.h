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

#define ceiling 3.8 // maximum distance by the Sensor

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

	void update(unsigned long ts) {
		if(type == IRD) {
			val = digitalRead(pin);
		}
		else if(type == IRSHORTL) {
			
			if(ts - timeStamp < 70000)
				return;
			val = analogRead(pin);
			oldDistance = distance;
			distance = 0.0;
			timeAvg = 0.0;
			speed = 0.0;
			for(int i = 0; i < CHAINSIZE - 1; i++) {
    			chain[i] = chain[i + 1];
    			timeChain[i] = timeChain[i + 1];
    			timeAvg += timeChain[i + 1];
    			speedChain[i] = speedChain[i + 1];
    			distance += chain[i + 1];
    			speed += speedChain[i + 1];
    		}
			chain[CHAINSIZE - 1] = (454.1513/(val + -52.5) + -1.059);
			// if(chain[CHAINSIZE - 1] >= ceiling || chain[CHAINSIZE - 1] <= -0.1) 
			// 	resetChain();
			// else 
				chain[CHAINSIZE - 1] /= 5.0;
			timeChain[CHAINSIZE - 1] = (ts - timeStamp) / 1000000.0;
			distance += chain[4];
			distance = distance;
			speedChain[CHAINSIZE - 1] = (chain[CHAINSIZE - 1] - chain[0]) / (timeAvg);
			speed += speedChain[CHAINSIZE - 1] / 5.0;
			timeStamp = ts;
			//Serial.println(distance);					
		}
		else if(type == IRSHORTR) {
			

			if(ts - timeStamp < 70000)
				return;
			val = analogRead(pin);
			oldDistance = distance;
			distance = 0.0;
			timeAvg = 0.0;
			speed = 0.0;
			for(int i = 0; i < CHAINSIZE - 1; i++) {
    			chain[i] = chain[i + 1];
    			timeChain[i] = timeChain[i + 1];
    			timeAvg += timeChain[i + 1];
    			speedChain[i] = speedChain[i + 1];
    			distance += chain[i + 1];
    			speed += speedChain[i + 1];
    		}
			chain[CHAINSIZE - 1] = 505.72/(val - 45.76) + -1.104;
			if(abs(speedChain[CHAINSIZE - 1]) > 5) { //(chain[CHAINSIZE - 1] >= ceiling || chain[CHAINSIZE - 1] <= -0.1) 
			 	resetChain();

			 }
			else 
				chain[CHAINSIZE - 1] /= 5.0;
			timeChain[CHAINSIZE - 1] = (ts - timeStamp) / 1000000.0;
			distance += chain[4];
			distance =distance;
			speedChain[CHAINSIZE - 1] = (chain[CHAINSIZE - 1] - chain[0]) / (timeAvg);
			speed += speedChain[CHAINSIZE - 1] / 5.0;
			timeStamp = ts;
			// /Serial.println(distance);
			// /Serial.println(speed);
		}
		else if(type == IR) {
			val = analogRead(pin);
			if(ts - timeStamp < 100000)
				return;
			oldDistance = distance;
			distance = 0.0;
			timeAvg = 0.0;
			speed = 0.0;
			for(int i = 0; i < CHAINSIZE - 1; i++) {
    			chain[i] = chain[i + 1];
    			timeChain[i] = timeChain[i + 1];
    			timeAvg += timeChain[i + 1];
    			speedChain[i] = speedChain[i + 1];
    			distance += chain[i + 1];
    			speed += speedChain[i + 1];
    		}
			chain[CHAINSIZE - 1] = (4406.752818/(val + 51.80904) + -1.74687) / 5.0;
			timeChain[CHAINSIZE - 1] = (ts - timeStamp) / 1000.0;
			distance += chain[4];

			speedChain[CHAINSIZE - 1] = (chain[CHAINSIZE - 1] - chain[0]) / (timeAvg);
			speed += speedChain[CHAINSIZE - 1] / 5.0;
			timeStamp = ts;
			//Serial.println(distance);
			//Serial.print("\t");
			//Serial.println(speed);
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