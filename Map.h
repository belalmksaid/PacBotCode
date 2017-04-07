#ifndef MAP
#define MAP

#include "Pos.h"
#include "Ghost.h"
#include "Driver.h"

#define BLOCK 0
#define PATH 1
#define ENTRANCE 2
#define VISITED 3

#define KeepForward 1
#define TurnRight 2
#define TurnLeft -2
#define TurnAround -1

class Map {
public:
	Map(Driver* d) {
		driver = d;
		ploc = new Pos(0,0,0,0,0);
	}

	char map[30][27] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1},
		{1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1},
		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
		{0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0},
		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
		{0,0,0,0,0,1,1,0,1,1,0,0,2,2,2,0,0,1,1,0,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
		{1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1},
		{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
		{0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,0,0},
		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	Pos* pac;
	//Ghost* g1, g2, g3, g4;
	Driver* driver;
	char options[4] = {5, 5, 5, 5};
	short noptions = 0;
	bool isLost = false;

	bool grace = false;
	bool busy = false;
	bool updateProjections = true;

	void init(int x1, int x2, int y1, int y2, char o) {
		pac = new Pos(x1, x2, y1, y2, o);
	}


	void update() {
		updateProj();
		updateBotPos();
		sync();
		// Serial.print(ploc->x1);
		// Serial.print("\t");
		// Serial.print(ploc->x2);
		// Serial.print("\t");
		// Serial.println(ploc->y1);
	}

	void getOptions() {
		noptions = 0;
		if(pac->orien == UP) {
			if(map[pac->x1][pac->y1 - 1] > 0 && map[pac->x2][pac->y1 - 1] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->x1][pac->y2 + 1] > 0 && map[pac->x2][pac->y2 + 1] > 0) {
				// options[noptions] = TurnAround;
				// noptions++;
			}
			if(map[pac->x1 - 1][pac->y1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->x1 + 1][pac->y1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
		}
		else if(pac->orien == DOWN) {
			if(map[pac->x1][pac->y1 - 1] > 0 && map[pac->x2][pac->y1 - 1] > 0) {
				// options[noptions] = TurnAround;
				// noptions++;
			}
			if(map[pac->x1][pac->y2 + 1] > 0 && map[pac->x2][pac->y2 + 1] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->x1 - 1][pac->y1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->x1 + 1][pac->y1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
		}
		else if(pac->orien == RIGHT) {
			if(map[pac->x1][pac->y1 - 1] > 0 && map[pac->x2][pac->y1 - 1] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->x1][pac->y2 + 1] > 0 && map[pac->x2][pac->y2 + 1] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->x1 - 1][pac->y1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				// options[noptions] = TurnAround;
				// noptions++;
			}
			if(map[pac->x1 + 1][pac->y1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
		}
		else if(pac->orien == LEFT) {
			if(map[pac->x1][pac->y1 - 1] > 0 && map[pac->x2][pac->y1 - 1] > 0) {
				options[noptions] = TurnRight;
				noptions++;
			}
			if(map[pac->x1][pac->y2 + 1] > 0 && map[pac->x2][pac->y2 + 1] > 0) {
				options[noptions] = TurnLeft;
				noptions++;
			}
			if(map[pac->x1 - 1][pac->y1] > 0 && map[pac->x1 - 1][pac->y2] > 0) {
				options[noptions] = KeepForward;
				noptions++;
			}
			if(map[pac->x1 + 1][pac->y1] > 0 && map[pac->x1 + 1][pac->y2] > 0) {
				//options[noptions] = TurnAround;
				//noptions++;
			}
		}

	}

	void updateOrien(char n) {
		pac->orien = n % 4;
	}

	char dir = -1;
	Pos* ploc;

	void updateProj() {
		if(updateProjections) {
			if(pac->orien == RIGHT) {
				for(short i = pac->x1; i < 27; i++) {
					//Serial.println(map[i][pac->y1 - 1] == 1);
					if(map[pac->y1 - 1][i] > 0 || map[i][pac->y2 + 1] > 0) {
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
				for(short i = pac->x1; i >= 0; i++) {
					if(map[pac->y1 - 1][i] > 0 || map[pac->y2 + 1][i] > 0) {
						ploc->x1 = i;
						ploc->x2 = i + 1;
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
				for(short i = pac->y1; i >= 0; i++) {
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
				for(short i = pac->y1; i < 30; i++) {
					if(map[i][pac->x1 - 1] > 0 || map[i][pac->x1 + 1] > 0) {
						ploc->x1 = pac->x1;
						ploc->x2 = pac->x2;
						ploc->y1 = i;
						ploc->y2 = i + 1;
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
			if(grace) {
				if(driver->rightD->getState() == COVERED && driver->leftD->getState() == COVERED) {
					grace == false;
				}
			}
			else {
				if((driver->rightD->getState() == OPEN && driver->leftD->getState() == OPEN && dir == 2) ||
					(driver->rightD->getState() == OPEN && dir == 0) || (driver->leftD->getState() == OPEN && dir == 1))
				 {
					pac->x1 = ploc->x1;
					pac->x2 = ploc->x2;
					pac->y1 = ploc->y1;
					pac->y2 = ploc->y2;
					pac->updatePos();
					dir = -1;
				}
				else if(dir != -1) {
					isLost = true;
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
			// Serial.print(pac->x1);
			// Serial.print("\t");
			// Serial.print(pac->x2);
			// Serial.print("\t");
			// Serial.println(pac->x);
		}
		else if(driver->status == TURNINGRIGHT) {
			if(!busy) {
				updateOrien(pac->orien + 1);
				busy = true;
				updateProjections = true;
				grace = true;
			}
		}
		else if(driver->status == TURNINGLEFT) { 
			if(!busy) {
				updateOrien(pac->orien + 1);
				busy = true;
				updateProjections = true;
			}
		}
		else if(driver->status == TURNINGBACK) {
			if(!busy) {
				updateOrien(pac->orien + 2);
				busy = true;
				updateProjections = true;
				grace = true;
			}
		}
	}


	void sync() {
	}

};

#endif
