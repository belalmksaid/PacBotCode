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
#define DEAD 4

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
		//d->setRight();
		//d->setCCW();
		//d->setStraight();

	}

	void update() {
		if(mode == DEAD)
			return;
		map->update();
		assessOptions();
	}

	void assessOptions() {
		if(driver->status == TURNINGLEFT || driver->status == TURNINGRIGHT || driver->status == TURNINGBACKCW || driver->status == TURNINGBACKCCW) { // if the robot is turning don't make any new decisions
			if(path->size <= 0) {
				driver->cutTime = millis();
				createPath();
				driver->cutTime = millis() - driver->cutTime + 1;
			}
			return;
		}
		if(!map->isLost) { // if we're not lost in the map
			if(decisionMade) { // we just finished a deicision
				driver->setStraight(); // set the robot straight after the decision's been made
				map->atDecisionPoint = false; // we're no longer at a decision point
				decisionMade = false; // we're not making a decision anymore
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

	char mode = SCATTER;

	vector<2> choice;

	#define oppositeDirections(a, b) ((a == RIGHT && b == LEFT) || (a == LEFT && b == RIGHT) || (a == UP && b == DOWN) || (a == DOWN && b == UP))
	#define inbetween(a, b, c) (false)

	void simpleAI() {
		if(mode == SCATTER) {
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			path->push(KeepForward);
			path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(KeepForward);
			path->push(TurnLeft);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			// path->push(TurnRight);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			// path->push(TurnLeft);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			// path->push(TurnLeft);
			// path->push(KeepForward);
			// path->push(TurnRight);
			// path->push(TurnLeft);
			// path->push(KeepForward);
			// path->push(KeepForward);
			// path->push(TurnRight);
			// path->push(TurnLeft);
			// path->push(TurnRight);
			// path->push(KeepForward);
			// path->push(TurnLeft);
			// path->push(TurnRight);
			// path->push(KeepForward);
			// path->push(TurnRight);
			// path->push(KeepForward);
			// path->push(TurnRight);
			// path->push(TurnRight);

		}
		else if(mode == CAUTIOUS) {
			choice[0] = -283712;
			choice[1] = -384738;
			map->getOptionsMod();
			for(int j = 0; j < 4; j++) { // iterate through ghosts
				pathAl.projectMod(&map->ghosts[j].pos, map->ghosts[j].pos.orien, map, map->ghosts[j].proj);
				int d = 12344;
				if((*map->ghosts[j].proj)[0] == -1) return;
				for(int i = 0; i < map->noptions; i++){
					vector<5> proj;
					pathAl.projectMod(map->pac, map->options[i], map, &proj);
					if(oppositeDirections(map->options[i], map->ghosts[j].pos.orien) && inbetween(map->ghosts[j].pos, map->pac, proj)) {
						return;
					}
					d = (*map->ghosts[j].proj)[4] + pathAl.shortestPathD(*(map->ghosts[j].proj), proj, map) + proj[4];
					d *= 10;
					d -= 590;
					if(d > choice[1]) {
						choice[0] = i;
						choice[1] = d;
					}
				}
			}
			if(choice[0] < 0) {
				r = (random(map->noptions));
				enforceChoice(map->options[r]);
			}
			else {	
				enforceChoice(map->options[choice[0]]);	
			}
		}
		else if(mode == CHASE) {

		}
	}

	void enforceChoice(char c) { // make the robot do the action picked
		if(c == map->pac->orien) {
			act(KeepForward);
		}
		else if(c - map->pac->orien == 1) {
			act(TurnRight);
		}
		else if(map->pac->orien - c == 1 || (map->pac->orien == UP && c == LEFT)) {
			act(TurnLeft);
		}
		else if(c - map->pac->orien == 2 || map->pac->orien - c == 2) {
			act(TurnAround);
		}
		else {
			//Serial.println("ERROR TURNING");
		}
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
	 // Check if the robot is asleep moving or if the robot is at a decision point
			simpleAI();
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
