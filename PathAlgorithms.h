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


class PathAl {
public:

	double estimateDistance(Node* a, Node *b) {
		return (3.5 * (abs(a->x2 - a->x1) + 1) + 3.5 * (abs(a->y2 - a->y1) + 1) / 7.0);
	}

	set<Node*>* nodeAStar(Node* start, Node* goal, SMap* m) {
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

	set<Node*>* nodeAStar(Pos* a, Pos* b, SMap* m) {
		return nodeAStar(m->getNode(a), m->getNode(b), m);
	}

	Path* getPath(set<Node*>* star, char o) {
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

	char setLeft(char o) {
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

	char setRight(char o) {
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

	char setUp(char o) {
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

	char setDown(char o) {
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
	short dx[4] = {0, 0, 1, -1};
	short dy[4] = {1, -1, 0, 0};

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

	vector<4> project(vector<4> pac, vector<2> dir, Map* map) {
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

	int z[4] = {1, -1, 0, 0};
	int z2[4] = {0, 0, -1, 1};

	#define distance(a, b) (a[0] < b[0] ?  b[0] - a[1] + 1 : a[0] > b[0] ? a[1] - b[0] + 1 : a[2] > b[2] ?  a[2] - b[3] + 1 : a[2] < b[2] ? b[2] - a[3] + 1 : 0)

	// int distance(vector<5> a, vector<5> b) {
	// 	if(a[0] < b[0]) {
	// 		return b[0] - a[1] + 1;
	// 	}
	// 	else if(a[0] > b[0]) {
	// 		return a[1] - b[0] + 1;
	// 	}
	// 	else if(a[2] > b[2]) {
	// 		return a[2] - b[3] + 1;
	// 	}
	// 	else if(a[2] < b[2]) {
	// 		return b[2] - a[3] + 1;
	// 	}
	// 	return 0;
	// }

	vector<5> projectMod(vector<5> pac, vector<2> dir, Map* map, int n) {
			vector<5> rv;
			rv[0] = -1;
			if(dir[0] == 1) {
				for(short i = pac[1] + 1; i < 28; i++) {
					if(isNode(pac[2], i)) {
						rv[0] = i;
						rv[1] = i + 1;
						rv[2] = pac[2];
						rv[3] = pac[3];
						rv[4] = n + distance(pac, rv);
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
						rv[4] = n + distance(pac, rv);
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
						rv[4] = n + distance(pac, rv);
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
						rv[4] = n + distance(pac, rv);
						return rv;					
					}
				}
			}
	}

	short dist[32][29];

	#define isTarget(a, t) (a[0] == t[0] && a[1] == t[1] && a[2] == t[2] && a[3] == t[3])
	#define visited(n) (dist[n[2]][n[0]] != -1)
	#define setVisited(n) dist[n[2]][n[0]] = n[4]
	#define val(n) dist[n[2]][n[0]]

	int shortestPathD(vector<4> c, vector<4> t, Map* map) {
		memset(dist, -1, sizeof(dist[0][0]) * 32 * 29);
		Queue<vector<5>> q;
		vector<5> start;
		start[0] = c[0];
		start[1] = c[1];
		start[2] = c[2];
		start[3] = c[3];
		val(start) = 0;
		// sset<svector<5>> visited;
		q.push(start);
		vector<2> dir;
		int d = 1293;
		while(q.size > 0) {
			vector<5> temp = q.pop();
		 	for(int i = 0; i < 4; i++) {
		 		dir[0] = z[i];
		 		dir[1] = z2[i];
		 		vector<5> n = projectMod(temp, dir, map, val(temp));
		 		if(n[0] < 0) continue;
	 			if(!visited(n)) {
	 				setVisited(n);
	 				if(isTarget(n, t)) {
	 					d = n[4];
	 				}
	 				else {
	 					q.push(n);
	 				}
	 			}
	 			else {
	 				if(n[4] < val(n)) {
	 					val(n) = n[4];
	 					q.push(n);
	 				}
	 				if(isTarget(n, t)) {
	 					d = val(n);

	 				}
	 			}
	  		}
		}
		return d;
	} 
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