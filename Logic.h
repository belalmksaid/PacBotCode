#ifndef LOGIC
#define LOGIC

#include "Driver.h"
#include "Map.h"
#include "Pos.h"

#define CAUTIOUS 0
#define CHASE 1
#define LOST 2

#define CCP false

class Logic {
public:
	long pos = 0;
	Logic(Driver* d, Map* m) {
		map = m;
		driver = d; 
		pos = d->leftMotor->encoderPos1;
		//d->setStraight();
		d->setCCW();
	}

	void update() {
		map->update();
		//assessOptions();
	}

	void assessOptions() {
		if(driver->status == TURNINGLEFT || driver->status == TURNINGRIGHT || driver->status == TURNINGBACKCW || driver->status == TURNINGBACKCCW) {

			return;
		}
		if(!map->isLost) {
			if(map->atDecisionPoint) {
				if(map->path->n > 0) {
					followPath();
				}
				else {
					createPath();
				}
			}
			else if(checkForInstaDeath()) {
				emergencyControl();
			}
		}
		else {
			wander();
		}

	}

	void act(short n) {
		if(n == TurnRight) {
			driver->setRight();
		}
		else if(n == TurnLeft) {
			driver->setLeft();
		}
		else if(n == KeepForward) {
			driver->setStraight();
		}
		// else {
		// 	driver->setCCW();
		// }
	}

	bool checkForInstaDeath() {
		return false;
	}

	void createPath() {
		if(CCP) {
			map->path->reset();
		}
		else {
			controlledWander();
		}

	}

	bool reaffirmPath() {
		return true;
	}

	void followPath() {
		if(reaffirmPath()) {
			act(map->path->pop());
		}
		else {
			createPath();
		}
	}
	int r = 0;
	void controlledWander() { // move randomly in the map, for testing only
		if(driver->status == SLEEP || map->atDecisionPoint) { // Check if the robot is asleep moving or if the robot is at a decision point
			map->getOptions(); // find possible options at the current block
			r = random(0, map->noptions);
			act(map->options[r]);
		}

	}

	void emergencyControl() {

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
