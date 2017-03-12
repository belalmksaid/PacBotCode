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

	void takeTimeA() {
		timestampA = millis();
	}

	void takeTimeB() {
		timestampB = millis();
	}

	void updateSensors() {
		gyro->update(timestampA, timestampF);
		fronts->update(timestampA);
		//lefts->update(timestampA);

	}

	void updateSensorsOnly() {
		takeTimeA();
		updateSensors();
		takeTimeB();
	}

	void update() {
		takeTimeA();
		updateSensors();
		driver->update(timestampA - timestampB);
		takeTimeB();
		
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