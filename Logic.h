#ifndef LOGIC
#define LOGIC

#include "Driver.h"
#include "Map.h"
#include "Pos.h"

#define CAUTIOUS 0
#define CHASE 1
#define LOST 2

class Logic {
public:
	long pos = 0;
	Logic(Driver* d, Map* m) {
		map = m;
		driver = d;
		pos = d->leftMotor->encoderPos1;
		d->setStraight();
	}

	void update() {
		map->update();
		wander();
		//assessOptions();
		/*if((driver->leftMotor->encoderPos1) * CONVERSION >= 15.75) {
			driver->freeze();
		}*/
	}

	void assessOptions() {
		if(!map->isLost) {
			if(hasPath) {
				if(checkForInstaDeath()) {
					makeDecision();
				}
				else {
					followPath();
				}
			}
			else {
				createPath();

			}
		}
		else {
			wander();
		}

	}

	void makeDecision() {

	}

	bool checkForInstaDeath() {
		return false;
	}

	void act() {

	}

	void createPath() {

	}

	void followPath() {

	}
	int r = 0;
	void wander() {
		if(driver->status != TURNINGLEFT && driver->status != TURNINGRIGHT) return;
		if(grace) {
			driver->setStraight();
			if(driver->rightD->getState() == COVERED && driver->leftD->getState() == COVERED) {
				grace = false;
			}
		}
		else {
			map->getOptions();
			r = random(0, map->noptions);
			if(map->options[r] == TurnRight) {
				driver->setRight();
				grace = true;
			}
			else if(map->options[r] == TurnLeft) {
				driver->setLeft();
				grace = true;
			}
		}

	}

private:
	Map* map;
	Driver* driver;
	int n;
	bool hasPath = false;
	char mode = CAUTIOUS;
	bool grace = false;
};

#endif
