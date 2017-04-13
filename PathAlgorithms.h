#ifndef PATHAL
#define PATHAL

#include "Path.h"
#include "Pos.h"
#include "Map.h"
#include "SMap.h"
#include "Util.h"



// class Node {
// public:
// 	Node* node;
// 	double f, g, h;
// 	double cost;
// 	Node* parent;

// 	Node(Node *n) {
// 		node = n;
// 		f = g = h = cost = 0.0;
// 		parent = NULL;
// 	}
// };

class PathAl {
public:

	static double estimateDistance(Node* a, Node *b) {
		return (3.5 * (abs(a->x2 - a->x1) + 1) + 3.5 * (abs(a->y2 - a->y1) + 1) / 7.0);
	}

	static set<Node*>* AStar(Node* start, Node* goal, SMap* m) {
		set<Node*> open;
		set<Node*> closed;

		start->g = 0;
		start->h = estimateDistance(start, goal);
		start->f = start->h;

		start->parent = NULL;

		open.add(start);

		short i = 0;

		Node* current = NULL;

		while(true) {
			current = NULL;

			if(open.size == 0) {
				Serial.println("No route.");
			}

			t<Node*> *iter = open.iterator();
			do {
				if(current == NULL || iter->data->f < current->f) {
					current = iter->data;
				}
			} while(iter->next != NULL);

			if(current == goal)
				break;

			open.remove(current);
			closed.add(current);

			for(i = 0; i < current->n; i++) {
				if(current->edges[i]->n > 1) {
					Node* neighbor = NULL;
					if(current->edges[i]->nodes[0] != current) {
						neighbor = current->edges[i]->nodes[0];
					}
					else {
						neighbor = current->edges[i]->nodes[1];
					}

					double nextG = current->g + current->edges[i]->length;

					if(nextG < neighbor->g) {
						open.remove(neighbor);
						closed.remove(neighbor);
					}

					if(!open.contains(neighbor) && !closed.contains(neighbor)) {
						neighbor->g = nextG;
						neighbor->h = estimateDistance(neighbor, goal);
						neighbor->f = neighbor->g + neighbor->h;
						neighbor->parent = current;
						open.add(neighbor);
					}
				}
			}
		}

		set<Node*>* rpath = new set<Node*>;

		current = goal;

		do {
			rpath->add(current);
			current = current->parent;
		}	while(current->parent != NULL);

		return rpath;
	}

	static set<Node*>* AStar(Pos* a, Pos* b, SMap* m) {
		return AStar(m->getNode(a), m->getNode(b), m);
	}

	static Path* getPath(set<Node*>* star, char o) {
		Path* rv = new Path;
		t<Node*> *it = star->iterator();
		t<Node*> *next = it->next;
		char prev = o;

		do {
			if(it->data->x2 < next->data->x1) {
				prev = setRight(prev);
				rv->push(prev, 0.00);
			}
			else if(it->data->x1 > next->data->x2) {
				prev = setLeft(prev);
				rv->push(prev, 0.0);
			}
			else if(next->data->y1 > it->data->y2) {
				prev = setUp(prev);
				rv->push(prev, 0.0);
			}
			else if(next->data->y2 < it->data->y1) {
				prev = setDown(prev);
				rv->push(prev, 0.0);
			}
		} while(it->next != NULL);
	}

	static char setLeft(char o) {
		if(o == UP) {
			return TurnLeft;
		}
		if(o == DOWN) {
			return TurnRight;
		}
		if(o == RIGHT) {
			return TurnAround;
		}
		if(o == LEFT)
			return KeepForward;
	}

	static char setRight(char o) {
		if(o == UP) {
			return TurnRight;
		}
		if(o == DOWN) {
			return TurnLeft;
		}
		if(o == RIGHT) {
			return KeepForward;
		}
		if(o == LEFT)
			return TurnAround;
	}

	static char setUp(char o) {
		if(o == UP) {
			return KeepForward;
		}
		if(o == DOWN) {
			return TurnAround;
		}
		if(o == RIGHT) {
			return TurnLeft;
		}
		if(o == LEFT)
			return TurnRight;
	}

	static char setDown(char o) {
		if(o == UP) {
			return TurnAround;
		}
		if(o == DOWN) {
			return KeepForward;
		}
		if(o == RIGHT) {
			return TurnRight;
		}
		if(o == LEFT)
			return TurnLeft;
	}
	
};

#endif