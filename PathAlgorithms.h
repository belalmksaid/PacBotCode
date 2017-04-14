#ifndef PATHAL
#define PATHAL

#include "Path.h"
#include "Pos.h"
#include "Map.h"
#include "SMap.h"
#include "Util.h"


#define isInRange(i, j) (i > 0 && j > 0 && i < 29 && j < 32)
#define isValid(a) (a[0] > 0 && a[2] > 0 && a[1] < 28 && a[3] < 31)
#define isNode(j, i) (map->map[j][i] == 6 || map->map[j][i] == 8)
#define length(v)  dist[v[2]][v[0]]

int dist[32][29];

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

	static set<Node*>* nodeAStar(Node* start, Node* goal, SMap* m) {
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

	static set<Node*>* nodeAStar(Pos* a, Pos* b, SMap* m) {
		return nodeAStar(m->getNode(a), m->getNode(b), m);
	}

	static Path* getPath(set<Node*>* star, char o) {
		Path* rv = new Path;
		t<Node*> *it = star->iterator();
		t<Node*> *next = it->next;
		char prev = o;

		do {
			if(it->data->x2 < next->data->x1) {
				prev = setRight(prev);
				rv->push(prev);
			}
			else if(it->data->x1 > next->data->x2) {
				prev = setLeft(prev);
				rv->push(prev);
			}
			else if(next->data->y1 > it->data->y2) {
				prev = setUp(prev);
				rv->push(prev);
			}
			else if(next->data->y2 < it->data->y1) {
				prev = setDown(prev);
				rv->push(prev);
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
	static constexpr short dx[4] = {0, 0, 1, -1};
	static constexpr short dy[4] = {1, -1, 0, 0};

	// static int mapAStar(int x1, int y1, int x2, int y2, char **map) {
	// 	Queue<vector<2>> q;
	// 	vector<2> start;
	// 	start[0] = x1;
	// 	start[1] = y1;
	// 	q.push(start);
	// 	memset(dist, -1, sizeof(dist[0][0] * 32 * 29));
	// 	dist[start[1]][start[0]] = 0;
	// 	while(q.size != 0) {
	// 		const vector<2> & p = q.pop();
	// 		for(short i = 0; i < 4; i++) {
	// 			int a = p[0] + dx[i];
	// 			int b = p[1] + dy[i];
	// 			if(a >= 0 && b >= 0 && a < 29 && b < 32 && dist[b][a] == -1 && map[b][a] != 0 ){
 //                    dist[a][b] = 1 + dist[p[1]][p[0]];
 //                    vector<2> n;
 //                    n[0] = b;
 //                    n[1] = a;
 //                    q.push(n);
 //                }
	// 		} 
	// 	}
	// 	return 0;
	// }

	static vector<4> project(vector<4> pac, vector<2> dir, Map* map) {
			vector<4> rv;
			rv[0] = -1;
			if(dir[0] == 1) {
				for(short i = pac[1] + 1; i < 28; i++) {
					if(isNode(pac[2], i)) {
						rv[0] = i;
						rv[1] = i + 1;
						rv[2] = pac[2];
						rv[3] = pac[3];
						return rv;
					}
				}

			}
			else if(dir[0] == -1) {
				for(short i = pac[0] - 1; i >= 1; i--) {
					if(isNode(pac[2], i)) {
						rv[0] = i - 1;
						rv[1] = i;
						rv[2] = pac[2];
						rv[3] = pac[3];
						return rv;
					}
				}
			}
			else if(dir[1] == -1) {
				for(short i = pac[2] - 1; i >= 1; i--) {
					if(isNode(i, pac[0])) {
						rv[0] = pac[0];
						rv[1] = pac[1];
						rv[2] = i - 1;
						rv[3] = i;
						return rv;
					}
				}
			}
			else {
				for(short i = pac[3] + 1; i < 31; i++) {
					if(isNode(i, pac[0])) {
						rv[0] = pac[0];
						rv[1] = pac[1];
						rv[2] = i;
						rv[3] = i + 1;
						return rv;					
					}
				}
			}
	}

	static constexpr int z[2] = {-1, 1};
	// static int mapBFSH(vector<4> c, vector<4> t, int l, Map* map) {
	// 	if(c == t)
	// 		return l;
	// 	if(isValid(c)) {
	// 		Serial.println(dist[c[2]][c[0]]);
	// 		if(l < length(c)) {
	// 			length(c) = l;
	// 			int temp1 = 2000;
	// 			for(int i = 0; i < 2; i++) {
	// 				for(int j = 0; j < 2; j++) {
	// 					vector<2> a;
	// 					a[0] = z[i];
	// 					a[1] = z[j];
	// 					vector<4> nn;
	// 					int temp2 = mapBFSH(project(c, a, map), t, l + 1, map);
	// 					if(temp2 < temp1) {
	// 						temp1 = temp2;
	// 					}
	// 				}
	// 			}
	// 			return temp1;
	// 		}
	// 		else {
	// 			return l;
	// 		}
	// 	}
	// 	else {
	// 		return 2000;
	// 	}
	// }


	// static int mapBFS(vector<4> a, vector<4> b, Map* map) {
	// 	for(int i = 0; i < 32; i++) {
	// 		for(int j = 0; j < 29; j++) {
	// 			dist[i][j] = 2000;
	// 		}
	// 	}
	// 	return mapBFSH(a, b, 0, map);
	// }
	
};

#endif