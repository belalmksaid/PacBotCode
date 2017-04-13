#ifndef SCHDLR
#define SCHDLR


#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"
//#include "GyroAccl.h"

#define frame() delay(10)

//#define GYROTIME 5


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
		rights->init();

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
		#ifdef ASENSOR
		// Serial.print(lefts->speed);
		// Serial.print("\t");
		// Serial.println(rights->speed);
		#endif
		driver->updateEncodersOnly(microA);
		fronts->update(microA);
		lefts->update(microA);
		rights->update(microA);
		rightD->update(timestampA);
		leftD->update(timestampA);

		// Serial.print(driver->rightD->getState());
		// Serial.print("\t");
		// Serial.println(rightD->getState());
	}

	void updateSensorsOnly() {
		takeTimeA();
		updateSensors();
		takeTimeB();
	}

	void update() {
		takeTimeA();
		updateSensors();
		driver->update(microA);
		frame();
		takeTimeB();
		loop++;
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
	//short gyroTime = GYROTIME;
};

#endif 