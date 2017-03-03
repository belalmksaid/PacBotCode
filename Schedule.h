#ifndef SCHDLR
#define SCHDLR


#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"
#include "GyroAccl.h"

#define GYROTIME 5


class Schedule {
public:
	Schedule(Driver* d, Sensor* a, Sensor* b, Sensor* c, Sensor* dd, GyroAccl* g) {
		gyro = g;
		fronts = a;
		backs = b;
		rights = c;
		lefts = dd;
		driver = d;
	}

	void init() {
		timestampF = millis();
	}

	void adjust() {
		gyro->update(timestampB);
		gyro->setDrift();
		timestampB = millis();
		//fronts->update(timestampA);
		//lefts->update(timestampA);
	}

	void update() {
		timestampA = millis();
		driver->update(timestampA - timestampB);
		gyro->update(timestampA - timestampB);
		if(gyroTime == 0) {
			
			gyroTime = GYROTIME;
		}
		else {
			//fronts->update(timestampA);
			//lefts->update(timestampA);
			gyroTime--;
		}
		timestampB = millis();
	}

private:
	unsigned long timestampF = 0;
	unsigned long timestampA = 0;
	unsigned long timestampB = 0;
	unsigned long loop = 0;
	Sensor* fronts;
	Sensor* backs;
	Sensor* lefts;
	Sensor* rights;
	GyroAccl* gyro;
	Driver* driver;
	short gyroTime = GYROTIME;
};

#endif 