#ifndef SCHDLR
#define SCHDLR


#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"
//#include "GyroAccl.h"

#define GYROTIME 5


class Schedule {
public:
	Schedule(Driver* d, Sensor* a, Sensor* b, Sensor* c, Sensor* dd, Sensor* rd, Sensor* ld) {
		//gyro = g;
		fronts = a;
		backs = b;
		rights = c;
		lefts = dd;
		driver = d;
		rightD = rd;
		leftD = ld;
	}

	void init() {
		timestampF = millis();
		fronts->init();
		leftD->init();
		rightD->init();
		lefts->init();

	}

	void takeTimeA() {
		timestampA = millis();
		microA = micros();
	}

	void takeTimeB() {
		timestampB = millis();
		microB = micros();
	}

	void updateSensors() {
		//gyro->update(timestampA, timestampF);
		fronts->update(timestampA);
		lefts->update(timestampA);
		Serial.println(lefts->getDistance());
		rightD->update(timestampA);
		leftD->update(timestampA);
		driver->updateEncodersOnly(microA);
		//rights->update(timestampA);

	}

	void updateSensorsOnly() {
		takeTimeA();
		updateSensors();
		takeTimeB();
	}

	void update() {
		takeTimeA();
		updateSensors();
		delay(50);
		driver->update();
		takeTimeB();
		
	}

private:
	unsigned long timestampF = 0;
	unsigned long timestampA = 0;
	unsigned long timestampB = 0;
	unsigned long microA = 0;
	unsigned long microB = 0;
	unsigned long loop = 0;
	Sensor* fronts;
	Sensor* backs;
	Sensor* lefts;
	Sensor* rights;
	Sensor* leftD;
	Sensor* rightD;
	//GyroAccl* gyro;
	Driver* driver;
	short gyroTime = GYROTIME;
};

#endif 