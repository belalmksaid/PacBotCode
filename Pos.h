#ifndef POS
#define POS

#define BLOCKSIZE 3.5
#define HBLOCKSIZE 1.75
#define BEPSILON 0.01

#define UP 0
#define DOWN 2
#define RIGHT 1
#define LEFT 3

#include "Arduino.h"

class Pos {
public:
	Pos(int _x1, int _x2, int _y1, int _y2, char o) {
		x1 = _x1;
		x2 = _x2;
		y1 = _y1;
		y2 = _y2;
		orien = o;
		updatePos();

	}
	Pos(double _x, double _y, char o) {
		x = _x;
		y = _y;
		orien = o;
		updateInd();
	}
	double x, y;
	int x1, x2, y1, y2;
	char orien;

	void updatePos() {
		x = ((x1 - 1.0) * 0.5 + (x2 - 1.0) * 0.5) * BLOCKSIZE + HBLOCKSIZE;
		y = ((y1 - 1.0) * 0.5 + (y2 - 1.0) * 0.5) * BLOCKSIZE + HBLOCKSIZE;
	}

	void updateInd() {
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
		y1++;
		y2++;
		x1++;
		x2++;
	}

	void print() {
		Serial.print(x1);
		Serial.print("\t");
		Serial.print(x2);
		Serial.print("\t");
		Serial.print(y1);
		Serial.print("\t");
		Serial.println(y2);
	}
	void printd() {
		Serial.print(x);
		Serial.print("\t");
		Serial.println(y);
	}

	int operator [](int i) const    {
		switch(i) {
			case 0:
				return x1;
			case 1:
				return x2;
			case 2:
				return y1;
			case 3:
				return y2;
		}
	}
    int& operator [](int i)    {
		switch(i) {
			case 0:
				return x1;
			case 1:
				return x2;
			case 2:
				return y1;
			case 3:
				return y2;
		}
	}
};



#endif