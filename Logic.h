#ifndef LOGIC
#define LOGIC

#include "Driver.h"
#include "Map.h"
#include "Pos.h"
#include "PathAlgorithms.h"

#define CAUTIOUS 0
#define CHASE 1
#define LOST 2

#define CCP false

class Logic {
public:
	long pos = 0;
	Path* path; // the directions that the robot is following right now
	PathAl pathAl;
	Logic(Driver* d, Map* m) {
		map = m;
		driver = d; 
		pos = d->leftMotor->encoderPos1;
		path = new Path();
		//d->setLeft();
		//d->setCCW();
		path->push(KeepForward);
		path->push(TurnRight);
		path->push(TurnLeft);
		path->push(TurnLeft);
		path->push(KeepForward);
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
			if(decisionMade) {
				driver->setStraight();
				map->atDecisionPoint = false;
				decisionMade = false;
			}
			if(map->atDecisionPoint || driver->status == SLEEP) {
				if(path->size > 0) {
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
		else {
			driver->setCCW();
		}
		decisionMade = true;
		map->grace = true;
	}

	bool checkForInstaDeath() {
		return false;
	}

	void createPath() {
		if(CCP) {
			path->reset();

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
			act(path->pop());
		}
		else {
			createPath();
		}
	}
	int r = 0;
	void controlledWander() { // move randomly in the map, for testing only
		if(driver->status == SLEEP || map->atDecisionPoint) { // Check if the robot is asleep moving or if the robot is at a decision point
			map->getOptions(); // find possible options at the current block
			// map->ploc->print();
			//Serial.println(map->noptions);
			// Serial.println((int)map->pac->orien);
			r = (random(map->noptions));
			act(map->options[r]);
			// driver->freeze();
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
	bool decisionMade = false;
};

#endif
