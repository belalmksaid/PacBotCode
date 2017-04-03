#ifndef POS
#define POS

#define BLOCKSIZE 3.5
#define HBLOCKSIZE 1.75
#define BEPSILON 0.01

#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#include "Arduino.h"

class Pos {
public:
	Pos(int _x1, int _x2, int _y1, int _y2, char o) {
		x1 = _x1;
		x2 = _x2;
		y1 = _y1;
		y2 = _y2;
		orien = o;
		getPos();

	}
	Pos(double _x, double _y, char o) {
		x = _x;
		y = _y;
		orien = o;
		getInd();
	}
	double x, y;
	int x1, x2, y1, y2;
	char orien;

	void getPos() {
		if(x1 == x2)
			x = x1 * BLOCKSIZE + HBLOCKSIZE;
		x = (x1 * 0.5 + x2 * 0.5) * BLOCKSIZE + HBLOCKSIZE;

		if(y1 == y2)
			y = y1 * BLOCKSIZE + HBLOCKSIZE;
		y = (y1 * 0.5 + y1 * 0.5) * BLOCKSIZE + HBLOCKSIZE;
	}

	void getInd() {
		double m = x / BLOCKSIZE;
		x1 = ((int)m);
		double r = x - x1 * BLOCKSIZE;
		if(abs(r - HBLOCKSIZE) < BEPSILON * 5.0) {
			x2 = x1;
		}
		else if(r >= HBLOCKSIZE) {
			x2 = x1 + 1;
		}
		else {
			x2 = x1;
			x1--;
		}

		m = y / BLOCKSIZE;
		y1 = ((int)m);
		r = y - y1 * BLOCKSIZE;
		if(abs(r - HBLOCKSIZE) < BEPSILON * 5.0) {
			y2 = y1;
		}
		else if(r >= HBLOCKSIZE) {
			y2 = y1 + 1;
		}
		else {
			y2 = y1;
			y1--;
		}
	}
};



#endif