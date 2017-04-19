#ifndef MAP
#define MAP

#include "Pos.h"
#include "Ghost.h"
#include "Driver.h"
//#include "SMap.h"
#include "Path.h"

#define BLOCK 0
#define PATH 1
#define ENTRANCE 2
#define VISITED 3

#define KeepForward 0
#define TurnRight 1
#define TurnLeft 3
#define TurnAround 2

#define PELLET 9
#define PELLETNODE 8
#define EATEN 7
#define EATENNODE 6
#define D 5
#define BLOCK 0
#define FORBIDDEN 2
#define LAST 4

class Map {
public:
	Map(Driver* d) {
		driver = d;
		ploc = new Pos(0,0,0,0,0);
		//solMap = new SMap();
	}

	char map[32][29] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,8,8,9,9,9,8,8,9,9,9,9,8,8,0,8,8,9,9,9,9,8,8,9,9,9,8,8,0},
		{0,8,8,9,9,9,8,8,9,9,9,9,8,8,0,8,8,9,9,9,9,8,8,9,9,9,8,8,0},
		{0,9,9,0,0,0,9,9,0,0,0,0,9,9,0,9,9,0,0,0,0,9,9,0,0,0,9,9,0},
		{0,9,9,0,0,0,9,9,0,0,0,0,9,9,0,9,9,0,0,0,0,9,9,0,0,0,9,9,0},
		{0,8,8,9,9,9,8,8,9,8,8,9,8,8,9,8,8,9,8,8,9,8,8,9,9,9,8,8,0},
		{0,8,8,9,9,9,8,8,9,8,8,9,8,8,9,8,8,9,8,8,9,8,8,9,9,9,8,8,0},
		{0,9,9,0,0,0,9,9,0,9,9,0,0,0,0,0,0,0,9,9,0,9,9,0,0,0,9,9,0},
		{0,8,8,9,9,9,8,8,0,8,8,9,8,8,0,8,8,9,8,8,0,8,8,9,9,9,8,8,0},
		{0,8,8,9,9,9,8,8,0,8,8,9,8,8,0,8,8,9,8,8,0,8,8,9,9,9,8,8,0},
		{0,0,0,0,0,0,9,9,0,0,0,0,9,9,0,9,9,0,0,0,0,9,9,0,0,0,0,0,0},
		{0,2,2,2,2,0,9,9,0,8,8,9,8,8,9,8,8,9,8,8,0,9,9,0,2,2,2,2,0},
		{0,2,2,2,2,0,9,9,0,8,8,9,8,8,9,8,8,9,8,8,0,9,9,0,2,2,2,2,0},
		{0,0,0,0,0,0,9,9,0,9,9,0,0,2,2,2,0,0,9,9,0,9,9,0,0,0,0,0,0},
		{0,9,9,9,9,9,8,8,9,8,8,0,2,2,2,2,2,0,8,8,9,8,8,9,9,9,9,9,0},
		{0,9,9,9,9,9,8,8,9,8,8,0,2,2,2,2,2,0,8,8,9,8,8,9,9,9,9,9,0},
		{0,0,0,0,0,0,9,9,0,9,9,0,0,0,0,0,0,0,9,9,0,9,9,0,0,0,0,0,0},
		{0,2,2,2,2,0,9,9,0,8,8,9,9,9,9,9,9,9,8,8,0,9,9,0,2,2,2,2,0},
		{0,2,2,2,2,0,9,9,0,8,8,9,9,9,9,9,9,9,8,8,0,9,9,0,2,2,2,2,0},
		{0,0,0,0,0,0,9,9,0,9,9,0,0,0,0,0,0,0,9,9,0,9,9,0,0,0,0,0,0},
		{0,8,8,9,9,9,8,8,9,8,8,9,8,8,0,8,8,9,8,8,9,8,8,9,9,9,8,8,0},
		{0,8,8,9,9,9,8,8,9,8,8,9,8,8,0,8,8,9,8,8,9,8,8,9,9,9,8,8,0},
		{0,9,9,0,0,0,9,9,0,0,0,0,9,9,0,9,9,0,0,0,0,9,9,0,0,0,9,9,0},
		{0,8,8,8,8,0,8,8,9,8,8,9,8,8,9,8,8,9,8,8,9,8,8,0,8,8,8,8,0},
		{0,8,8,8,8,0,8,8,9,8,8,9,8,8,9,8,8,9,8,8,9,8,8,0,8,8,8,8,0},
		{0,0,0,9,9,0,9,9,0,9,9,0,0,0,0,0,0,0,9,9,0,9,9,0,9,9,0,0,0},
		{0,8,8,8,8,9,8,8,0,8,8,9,8,8,0,8,8,9,8,8,0,8,8,9,8,8,8,8,0},
		{0,8,8,8,8,9,8,8,0,8,8,9,8,8,0,8,8,9,8,8,0,8,8,9,8,8,8,8,0},
		{0,9,9,0,0,0,0,0,0,0,0,0,9,9,0,9,9,0,0,0,0,0,0,0,0,0,9,9,0},
		{0,8,8,9,9,9,9,9,9,9,9,9,8,8,9,8,8,9,9,9,9,9,9,9,9,9,8,8,0},
		{0,8,8,9,9,9,9,9,9,9,9,9,8,8,9,8,8,9,9,9,9,9,9,9,9,9,8,8,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	Pos* pac;
	Ghost ghosts[4] = { Ghost(0,0,0,0, UP, BLINKY, this), Ghost(0,0,0,0, DOWN, INKY, this), Ghost(0,0,0,0, LEFT, PINKY, this), Ghost(0,0,0,0, UP, CLYDE, this) };
	Driver* driver;
	//SMap* solMap;
	char options[4] = {5, 5, 5, 5};
	short noptions = 0;
	bool isLost = false;
	bool grace = false;
	double dis = 0.0;

	int remainingFood = 10;


	bool busy = false; // used to update orientation once when the robot is turning
	bool updateProjections = true; // used to get a projection only once, saves calculation time
	bool atDecisionPoint = false; // tells logic if the robot is at a decision point

	void init(int x1, int x2, int y1, int y2, char o) {
		pac = new Pos(x1, x2, y1, y2, o);
		// /ghosts = { new Ghost(0,0,0,0, UP, BLINKY, this), g2 = new Ghost(0,0,0,0, DOWN, INKY, this), g3 = new Ghost(0,0,0,0, LEFT, PINKY, this), g4 = new Ghost(0,0,0,0, UP, CLYDE, this) };		
	}


	void update() {
		updateProj();
		updateBotPos();
	}

	void getOptions() {
		noptions = 0;
		if(pac->orien == UP) {
			if(map[pac->y1 - 1][pac->x1] > D && map[pac->y1 - 1][pac->x2] > D) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > D && map[pac->y2 + 1][pac->x2] > D) {
				options[noptions] = TurnAround;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > D && map[pac->y2][pac->x1 - 1] > D) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->y1][pac->x2 + 1] > D && map[pac->y2][pac->x2 + 1] > D) {
				options[noptions] = TurnRight;
				noptions++;
			}
		}
		else if(pac->orien == DOWN) {
			if(map[pac->y1 - 1][pac->x1] > D && map[pac->y1 - 1][pac->x2] > D) {
				options[noptions] = TurnAround;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > D && map[pac->y2 + 1][pac->x2] > D) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > D && map[pac->y2][pac->x1 - 1] > D) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > D && map[pac->y2][pac->x1 + 1] > D) {
				options[noptions] = TurnLeft;
				noptions++;
			}
		}
		else if(pac->orien == RIGHT) {
			if(map[pac->y1 - 1][pac->x1] > D && map[pac->y1 - 1][pac->x2] > D) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > D && map[pac->y2 + 1][pac->x2] > D) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > D && map[pac->y2][pac->x1 - 1] > D) {
				options[noptions] = TurnAround;
				noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > D && map[pac->y2][pac->x1 + 1] > D) {
				options[noptions] = KeepForward;
				noptions++;
			}
		}
		else if(pac->orien == LEFT) {
			if(map[pac->y1 - 1][pac->x1] > D && map[pac->y1 - 1][pac->x2] > D) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > D && map[pac->y2 + 1][pac->x2] > D) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > D && map[pac->y2][pac->x1 - 1] > D) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > D && map[pac->y2][pac->x1 + 1] > D) {
				options[noptions] = TurnAround;
				noptions++;
			}
		}

	}

	void getOptionsMod() {
		noptions = 0;
		if(map[pac->y1 - 1][pac->x1] > D && map[pac->y1 - 1][pac->x2] > D) {
			options[noptions] = UP;
			noptions++;
		}
		if(map[pac->y2 + 1][pac->x1] > D && map[pac->y2 + 1][pac->x2] > D) {
			options[noptions] = DOWN;
			noptions++;
		}
		if(map[pac->y1][pac->x1 - 1] > D && map[pac->y2][pac->x1 - 1] > D) {
			options[noptions] = LEFT;
			noptions++;
		}
		if(map[pac->y1][pac->x2 + 1] > D && map[pac->y2][pac->x2 + 1] > D) {
			options[noptions] = RIGHT;
			noptions++;
		}
	}

	void updateOrien(char n) {
		pac->orien = n % 4;
	}

	char dir = -1; // 1 is left, 2 is both 0 is right
	Pos* ploc;

	void updateProj() {
		if(updateProjections) {
			if(pac->orien == RIGHT) {
				for(short i = pac->x2 + 1; i < 28; i++) {
					if(map[pac->y1 - 1][i] > D || map[pac->y2 + 1][i] > D) {
						ploc->x1 = i;
						ploc->x2 = i + 1;
						ploc->y1 = pac->y1;
						ploc->y2 = pac->y2;
						if(map[pac->y1 - 1][i] > D &&  map[pac->y2 + 1][i] > D) {
							dir = 2;
						}
						else if(map[pac->y2 + 1][i] > D) {
							dir = 0;
						}
						else {
							dir = 1;
						}
						break;
					}
				}

			}
			else if(pac->orien == LEFT) {
				for(short i = pac->x1 - 1; i >= 1; i--) {
					if(map[pac->y1 - 1][i] > D || map[pac->y2 + 1][i] > D) {
						ploc->x1 = i - 1;
						ploc->x2 = i;
						ploc->y1 = pac->y1;
						ploc->y2 = pac->y2;
						if(map[pac->y1 - 1][i] > D &&  map[pac->y2 + 1][i] > D) {
							dir = 2;
						}
						else if(map[pac->y2 + 1][i]> D) {
							dir = 1;
						}
						else {
							dir = 0;
						}
						break;
					}
				}
			}
			else if(pac->orien == UP) {
				for(short i = pac->y1 - 1; i >= 1; i--) {
					if(map[i][pac->x1 - 1] > D || map[i][pac->x2 + 1] > D) {
						ploc->x1 = pac->x1;
						ploc->x2 = pac->x2;
						ploc->y1 = i - 1;
						ploc->y2 = i;
						if(map[i][pac->x1 - 1] > D &&  map[i][pac->x2 + 1] > D) {
							dir = 2;
						}
						else if(map[i][pac->x2 + 1] > D) {
							dir = 0;
						}
						else {
							dir = 1;
						}
						break;
					}
				}
			}
			else {
				for(short i = pac->y2 + 1; i < 31; i++) {
					if(map[i][pac->x1 - 1] > D || map[i][pac->x2 + 1] > D) {
						ploc->x1 = pac->x1;
						ploc->x2 = pac->x2;
						ploc->y1 = i;
						ploc->y2 = i + 1;
						if(map[i][pac->x1 - 1] > D &&  map[i][pac->x2 + 1] > D) {
							dir = 2;
						}
						else if(map[i][pac->x2 + 1] > D) {
							dir = 1;
						}
						else {
							dir = 0;
						}
						break;						
					}
				}
			}
			updateProjections = false;
		}

	}

	void eatFood(Pos* o, Pos* n) {
		int mix = min(o->x1, n->x1);
		int max = max(o->x2, n->x2);

		int miy = min(o->y1, n->y1);
		int may = max(o->y2, n->y2);

		for(int i = mix; i <= max; i++) {
			for(int j = miy; j <= may; j++) {
				if(map[j][i] > 7) {
					remainingFood--;
					map[j][i] -= 2;
				}
			}
		}
	}

	void print() {
		for(int x = 0; x < 32; x++) {
			for(int y = 0; y < 29; y++) {
				Serial.print((int)map[x][y]);
				Serial.print(" ");
			}
			Serial.println();
		}
	}

	void reset() {
		dir = -1;
	}

	void updateBotPos() {
		if(driver->status == MOVINGFORWARD) {
			busy = false;
			if(!grace && (((driver->rightD->getState() == OPEN && driver->leftD->getState() == OPEN && dir == 2) ||
				(driver->leftD->getState() == COVERED && driver->rightD->getState() == OPEN && dir == 0) || (driver->leftD->getState() == OPEN && driver->rightD->getState() == COVERED && dir == 1))))
			{
				pac->x1 = ploc->x1;
				pac->x2 = ploc->x2;
				pac->y1 = ploc->y1;
				pac->y2 = ploc->y2;
				pac->updatePos();
				//solMap->updateCurrentNode(pac);
				dir = -1;
				atDecisionPoint = true;
				updateProjections = true;
			}
			else if(grace) {
				dis += abs((driver->leftMotor->distance + driver->rightMotor->distance)) * 0.5;
				if(dis >= 7.0) {
					grace = false;
					dis = 0.0;
				}
			}

			switch(pac->orien) {
				case UP:
				pac->y -= (driver->leftMotor->distance + driver->rightMotor->distance) * 0.5;
				pac->updateInd();
				break;
				case DOWN:
				pac->y += (driver->leftMotor->distance + driver->rightMotor->distance) * 0.5;
				pac->updateInd();
				break;
				case RIGHT:
				pac->x += (driver->leftMotor->distance + driver->rightMotor->distance) * 0.5;
				pac->updateInd();
				break;
				case LEFT:
				pac->x -= (driver->leftMotor->distance + driver->rightMotor->distance) * 0.5;
				pac->updateInd();
				break;
			}
		}
		else if(driver->status == TURNINGRIGHT) {
			grace = true;
			if(!busy) {
				updateOrien(pac->orien + 1);
				busy = true;
				updateProjections = true;
			}
		}
		else if(driver->status == TURNINGLEFT) { 
			grace = true;
			if(!busy) {
				updateOrien(pac->orien - 1);
				busy = true;
				updateProjections = true;
				grace = true;
			}
		}
		else if(driver->status == TURNINGBACKCW || driver->status == TURNINGBACKCCW) {
			grace = true;
			if(!busy) {
				updateOrien(pac->orien + 2);
				busy = true;
				updateProjections = true;
			}
		}
		else {
			busy = false;
		}
	}
};

#endif
