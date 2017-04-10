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
		//d->setStraight();
		//d->setAdjust();
	}

	void update() {
		// if(driver->status == SLEEP) {
		// 	driver->setStraight();
		// }
		// else if(driver->fronts->distance <= 6) {
		// 	driver->setCCW();
		// }
		map->update();
		controlledWander();
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
	void controlledWander() { // move randomly in the map, for testing only
		if(driver->status == TURNINGLEFT || driver->status == TURNINGRIGHT || driver->status == TURNINGBACKCW || driver->status == TURNINGBACKCCW) return;
		

		if(driver->status == SLEEP || map->atDecisionPoint) { // Check if the robot is asleep moving or if the robot is at a decision point
			map->getOptions(); // find possible options at the current block
			r = random(0, map->noptions);
			if(map->options[r] == TurnRight) {
				driver->setRight();
				Serial.println((int)map->options[r]);
			}
			else if(map->options[r] == TurnLeft) {
				driver->setLeft();
			}
			else if(map->options[r] == KeepForward) {
				driver->setStraight();
			}
		}

	}

	void wander() {

	}

private:
	Map* map;
	Driver* driver;
	int n;
	bool hasPath = false;
	char mode = CAUTIOUS;
};

#endif
