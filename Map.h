#ifndef MAP
#define MAP

#include "Pos.h"
#include "Ghost.h"
#include "Driver.h"
#include "SMap.h"
#include "Path.h"

#define BLOCK 0
#define PATH 1
#define ENTRANCE 2
#define VISITED 3

#define KeepForward 1
#define TurnRight 2
#define TurnLeft -2
#define TurnAround -1

#define PELLET 1
#define BLOCK 0
#define FORBIDDEN 2
#define EATEN 3
#define LAST 4

// char map[30][27] = {
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1},
// 		{1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1},
// 		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
// 		{0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0},
// 		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
// 		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
// 		{0,0,0,0,0,1,1,0,1,1,0,0,2,2,2,0,0,1,1,0,1,1,0,0,0,0,0},
// 		{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
// 		{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
// 		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
// 		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
// 		{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1},
// 		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
// 		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
// 		{0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0},
// 		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
// 		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 	};
	


class Map {
public:
	Map(Driver* d) {
		driver = d;
		ploc = new Pos(0,0,0,0,0);
		solMap = new SMap();
	}

	char map[32][29] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0},
		{0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0},
		{0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0},
		{0,0,0,0,0,0,1,1,0,1,1,0,0,2,2,2,0,0,1,1,0,1,1,0,0,0,0,0,0},
		{0,4,4,4,4,4,1,1,1,1,1,0,2,2,2,2,2,0,1,1,1,1,1,4,4,4,4,4,0},
		{0,4,4,4,4,4,1,1,1,1,1,0,2,2,2,2,2,0,1,1,1,1,1,4,4,4,4,4,0},
		{0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0},
		{0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0},
		{0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0},
		{0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
		{0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
		{0,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0},
		{0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0},
		{0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	Pos* pac;
	Ghost* g1, *g2, *g3, *g4;
	Driver* driver;
	SMap* solMap;
	short options[4] = {5, 5, 5, 5};
	short noptions = 0;
	bool isLost = false;

	Path* path;


	bool busy = false; // used to update orientation once when the robot is turning
	bool updateProjections = true; // used to get a projection only once, saves calculation time
	bool atDecisionPoint = false; // tells logic if the robot is at a decision point

	void init(int x1, int x2, int y1, int y2, char o) {
		pac = new Pos(x1, x2, y1, y2, o);
		g1 = new Ghost(0,0,0,0, UP, BLINKY, this);
		g2 = new Ghost(0,0,0,0, DOWN, INKY, this);
		g3 = new Ghost(0,0,0,0, LEFT, PINKY, this);
		g4 = new Ghost(0,0,0,0, UP, CLYDE, this);
	}


	void update() {
		updateProj();
		updateBotPos();
	}

	void getOptions() {
		noptions = 0;
		if(pac->orien == UP) {
			if(map[pac->y1 - 1][pac->x1] > 0 && map[pac->y1 - 1][pac->x2] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > 0 && map[pac->y2 + 1][pac->x2] > 0) {
				// options[noptions] = TurnAround;
				// noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
		}
		else if(pac->orien == DOWN) {
			if(map[pac->y1 - 1][pac->x1] > 0 && map[pac->y1 - 1][pac->x2] > 0) {
				// options[noptions] = TurnAround;
				// noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > 0 && map[pac->y2 + 1][pac->x2] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
		}
		else if(pac->orien == RIGHT) {
			// Serial.println(pac->x1);
			// Serial.println(pac->y2);
			// Serial.println("wtf");
			// Serial.println((int)map[pac->y2 + 1][pac->x1]);
			if(map[pac->y1 - 1][pac->x1] > 0 && map[pac->y1 - 1][pac->x2] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > 0 && map[pac->y2 + 1][pac->x2] > 0) {
				// Serial.println((int)map[pac->y2 + 1][pac->x2]);
				// Serial.println(pac->x1);
				// Serial.println(pac->y2 + 1);
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				// options[noptions] = TurnAround;
				// noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
		}
		else if(pac->orien == LEFT) {
			if(map[pac->y1 - 1][pac->x1] > 0 && map[pac->y1 - 1][pac->x2] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->y2 + 1][pac->x1] > 0 && map[pac->y2 + 1][pac->x2] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->y1][pac->x1 - 1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->y1][pac->x1 + 1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				//options[noptions] = TurnAround;
				//noptions++;
			}
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
				for(short i = pac->x1; i < 28; i++) {
					if(map[pac->y1 - 1][i] > 0 || map[pac->y2 + 1][i] > 0) {
						ploc->x1 = i;
						ploc->x2 = i + 1;
						ploc->y1 = pac->y1;
						ploc->y2 = pac->y2;
						if(map[pac->y1 - 1][i] > 0 &&  map[pac->y2 + 1][i] > 0) {
							dir = 2;
						}
						else if(map[pac->y2 + 1][i] > 0) {
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
				for(short i = pac->x1; i >= 1; i--) {
					if(map[pac->y1 - 1][i] > 0 || map[pac->y2 + 1][i] > 0) {
						ploc->x1 = i - 1;
						ploc->x2 = i;
						ploc->y1 = pac->y1;
						ploc->y2 = pac->y2;
						if(map[pac->y1 - 1][i] > 0 &&  map[pac->y2 + 1][i] > 0) {
							dir = 2;
						}
						else if(map[pac->y2 + 1][i]> 0) {
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
				for(short i = pac->y1; i >= 1; i++) {
					if(map[i][pac->x1 - 1] > 0 || map[i][pac->x1 + 1] > 0) {
						ploc->x1 = pac->x1;
						ploc->x2 = pac->x2;
						ploc->y1 = i;
						ploc->y2 = i + 1;
						if(map[i][pac->x1 - 1] > 0 &&  map[i][pac->x1 + 1] > 0) {
							dir = 2;
						}
						else if(map[i][pac->x2 + 1] > 0) {
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
				for(short i = pac->y1; i < 31; i--) {
					if(map[i][pac->x1 - 1] > 0 || map[i][pac->x1 + 1] > 0) {
						ploc->x1 = pac->x1;
						ploc->x2 = pac->x2;
						ploc->y1 = i - 1;
						ploc->y2 = i;
						if(map[i][pac->x1 - 1] > 0 &&  map[i][pac->x1 + 1] > 0) {
							dir = 2;
						}
						else if(map[i][pac->x2 + 1] > 0) {
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

	void updateBotPos() {
		if(driver->status == MOVINGFORWARD) {
			busy = false;
			if(dir != -1 && ((driver->rightD->getState() == OPEN && driver->leftD->getState() == OPEN && dir == 2) ||
				(driver->rightD->getState() == OPEN && dir == 0) || (driver->leftD->getState() == OPEN && dir == 1)))
			{
				pac->x1 = ploc->x1;
				pac->x2 = ploc->x2;
				pac->y1 = ploc->y1;
				pac->y2 = ploc->y2;
				pac->updatePos();
				solMap->updateCurrentNode(pac);
				dir = -1;
				atDecisionPoint = true;

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
			if(!busy) {
				updateOrien(pac->orien + 1);
				busy = true;
				updateProjections = true;
			}
		}
		else if(driver->status == TURNINGLEFT) { 
			if(!busy) {
				updateOrien(pac->orien - 1);
				busy = true;
				updateProjections = true;
			}
		}
		else if(driver->status == TURNINGBACKCW || driver->status == TURNINGBACKCCW) {
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
