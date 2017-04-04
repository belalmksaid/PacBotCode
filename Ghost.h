#ifndef GHOST
#define GHOST


#define BLINKY 0
#define PINKY 1
#define INKY 2
#define CLYDE 3

#include "Pos.h"

class Ghost {
public:
	char color;
	Ghost(int x1, int x2, int y1, int y2, char o, char id, char** m) : pos(x1, x2, y1, y2, o) {
		color = id;
		map = m;
	}

	Pos* projected() {
		return proj;
	}

	void update(int x1, int x2, int y1, int y2) {

	}

private:
	Pos pos;
	Pos* proj;
	char** map;

};

#endif