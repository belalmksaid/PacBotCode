#ifndef SMAP
#define SMAP

#include "Pos.h"
#include "Ghost.h"
#include "Driver.h"

#define BLOCK 0
#define PATH 1
#define ENTRANCE 2
#define VISITED 3

#define Horizontal 0
#define Vertical 1

struct Edge;

struct Node {
	double x = 0.0, y = 0.0;
	int n = 0;
	Edge *a, *b, *c, *d;

};

struct Edge {
	char o = 0;
	Node *a, *b;


};

class SMap {
public:
	SMap(Driver* d) {

	}

};

#endif SMAP