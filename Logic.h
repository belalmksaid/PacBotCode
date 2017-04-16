#ifndef LOGIC
#define LOGIC

#include "Driver.h"
#include "Map.h"
#include "Pos.h"
#include "PathAlgorithms.h"

#define CAUTIOUS 0
#define CHASE 1
#define LOST 2
#define SCATTER 3

#define CCP false //If the robot is allowed to generate paths

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

	char mode = CAUTIOUS;

	vector<2> choice;

	void simpleAI() {
		if(mode == SCATTER) {
			path->push(KeepForward);
			path->push(TurnRight);
			path->push(TurnLeft);
			path->push(TurnLeft);
			path->push(KeepForward);
		}
		else if(mode == CAUTIOUS) {
			map->getOptionsMod();
			for(int i = 0; i < map->noptions; i++) {
				vector<5> proj = pathAl.projectMod(map->pac, map->options[i], map);
				int d = 12344;
				for(int j = 0; j < 4; j++) {
					*(map->ghosts[i].proj) = pathAl.projectMod(&map->ghosts[i].pos, map->ghosts[i].pos.orien, map);
					d = (*map->ghosts[i].proj)[4] + pathAl.shortestPathD(*(map->ghosts[i].proj), proj, map) + proj[4];
					d *= 10;
					d -= 590;
					if(d > choice[1]) {
						choice[0] = i;
						choice[1] = d;
					}
				}
			}

			enforceChoice(map->options[choice[0]]);	
		}
	}

	void enforceChoice(char c) {

	}

	int scoreChoice(vector<5> *c) {

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
	void controlledWander() { // avoids ghosts only, doesn't care about food doesn't plan very far ahead
		if(driver->status == SLEEP || map->atDecisionPoint) { // Check if the robot is asleep moving or if the robot is at a decision point
			simpleAI();
		}

	}

	void emergencyControl() {

	}

	void wander() { // moves around randomly
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

private:
	Map* map;
	Driver* driver;
	int n;
	bool hasPath = false;
	bool decisionMade = false;
};

#endif
