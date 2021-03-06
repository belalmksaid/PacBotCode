#ifndef GHOST
#define GHOST


#define BLINKY 0
#define PINKY 1
#define INKY 2
#define CLYDE 3

#include "Pos.h"
#include "Map.h"
#include "Util.h"

class Map;

class Ghost {
public:
	Pos pos;
	vector<5>* proj;
	char color;
	Ghost(int x1, int x2, int y1, int y2, char o, char id, Map* const m) : pos(x1, x2, y1, y2, o) {
		color = id;
		map = m;
		proj = new vector<5>;
		(*proj)[0] = -1;
	}

	vector<5>* projected() {
		return proj;
	}

	void update(int x1, int x2, int y1, int y2) {
		pos.x1 = x1;
		pos.x2 = x2;
		pos.y1 = y2;
		pos.y2 = y2;
	}

private:

	Map* map;
};

#endif