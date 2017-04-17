#ifndef PATHAL
#define PATHAL

#include "Path.h"
#include "Pos.h"
#include "Map.h"
//#include "SMap.h"
#include "Util.h"



#define isInRange(i, j) (i > 0 && j > 0 && i < 29 && j < 32)
#define isValid(a) (a[0] > 0 && a[2] > 0 && a[1] < 28 && a[3] < 31)

#define length(v)  dist[v[2]][v[0]]


class PathAl {
public:

	// Path* getPath(set<Node*>* star, char o) {
	// 	Path* rv = new Path;
	// 	t<Node*> *it = star->iterator();
	// 	t<Node*> *next = it->next;
	// 	char prev = o;

	// 	do {
	// 		if(it->data->x2 < next->data->x1) {
	// 			prev = setRight(prev);
	// 			rv->push(prev);
	// 		}
	// 		else if(it->data->x1 > next->data->x2) {
	// 			prev = setLeft(prev);
	// 			rv->push(prev);
	// 		}
	// 		else if(next->data->y1 > it->data->y2) {
	// 			prev = setUp(prev);
	// 			rv->push(prev);
	// 		}
	// 		else if(next->data->y2 < it->data->y1) {
	// 			prev = setDown(prev);
	// 			rv->push(prev);
	// 		}
	// 	} while(it->next != NULL);
	// 	return rv;
	// }

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

	#define distance(a, b) (a[0] < b[0] ?  b[0] - a[1] + 1 : a[0] > b[0] ? a[1] - b[0] + 1 : a[2] > b[2] ?  a[2] - b[3] + 1 : a[2] < b[2] ? b[2] - a[3] + 1 : 0)
	#define isNode(j, i) (map->map[j][i] == 6 || map->map[j][i] == 8)
	#define isFood(j, i) (map->map[j][i] == 8 || map->map[j][i] == 9)

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
			} // find the next node in this direction, returns the node and distance
	}

	vector<5> projectMod(Pos* pac, char dir, Map* map) {
		vector<5> rv;
		rv[0] = -1;
		rv[4] = 2;
		switch(dir) {
			case RIGHT: {
				for(short i = (*pac)[1] + 1; i < 28; i++) {
					rv[4] += 1;
					if(isNode((*pac)[2], i)) {
						rv[0] = i;
						rv[1] = i + 1;
						rv[2] = (*pac)[2];
						rv[3] = (*pac)[3];
						//rv[4] =  distance((*pac), rv);
						return rv;
					}
				}

			}
			case LEFT: {
				for(short i = (*pac)[0] - 1; i >= 1; i--) {
					rv[4] += 1;
					if(isNode((*pac)[2], i)) {
						rv[0] = i - 1;
						rv[1] = i;
						rv[2] = (*pac)[2];
						rv[3] = (*pac)[3];
						//rv[4] = distance((*pac), rv);
						return rv;
					}
				}
			}
			case UP: 
			{
				for(short i = (*pac)[2] - 1; i >= 1; i--) {
					rv[4] += 1;
					if(isNode(i, (*pac)[0])) {
						rv[0] = (*pac)[0];
						rv[1] = (*pac)[1];
						rv[2] = i - 1;
						rv[3] = i;
						//rv[4] = distance((*pac), rv);
						return rv;
					}
				}
			}
			case DOWN: 
			{
				for(short i = (*pac)[3] + 1; i < 31; i++) {
					rv[4] += 1;
					if(isNode(i, (*pac)[0])) {
						rv[0] = (*pac)[0];
						rv[1] = (*pac)[1];
						rv[2] = i;
						rv[3] = i + 1;
						//rv[4] = distance((*pac), rv);
						return rv;					
					}
				}
			}
		} // find the next node in the given direction, returns the node and distance
	}

	vector<6> projectModFood(Pos* pac, char dir, Map* map, int n, int f) { // find the next node in the given direction, returns the node and distance and that value of the food in those nodes
		vector<6> rv;
		rv[0] = -1;
		rv[4] = 2 + n;
		rv[5] = f;
		switch(dir) {
			case RIGHT: {
				for(short i = (*pac)[1] + 1; i < 28; i++) {
					rv[4] += 1;
					rv[5] += isFood((*pac)[2], i) ? 1 : 0; 
					if(isNode((*pac)[2], i)) {
						rv[0] = i;
						rv[1] = i + 1;
						rv[2] = (*pac)[2];
						rv[3] = (*pac)[3];
						//rv[4] =  distance((*pac), rv);
						return rv;
					}
				}

			}
			case LEFT: {
				for(short i = (*pac)[0] - 1; i >= 1; i--) {
					rv[4] += 1;
					rv[5] += isFood((*pac)[2], i) ? 1 : 0; 
					if(isNode((*pac)[2], i)) {
						rv[0] = i - 1;
						rv[1] = i;
						rv[2] = (*pac)[2];
						rv[3] = (*pac)[3];
						//rv[4] = distance((*pac), rv);
						return rv;
					}
				}
			}
			case UP: 
			{
				for(short i = (*pac)[2] - 1; i >= 1; i--) {
					rv[4] += 1;
					rv[5] += isFood(i, (*pac)[0]) ? 1 : 0; 
					if(isNode(i, (*pac)[0])) {
						rv[0] = (*pac)[0];
						rv[1] = (*pac)[1];
						rv[2] = i - 1;
						rv[3] = i;
						//rv[4] = distance((*pac), rv);
						return rv;
					}
				}
			}
			case DOWN: 
			{
				for(short i = (*pac)[3] + 1; i < 31; i++) {
					rv[4] += 1;
					rv[5] += isFood(i, (*pac)[0]) ? 1 : 0; 
					if(isNode(i, (*pac)[0])) {
						rv[0] = (*pac)[0];
						rv[1] = (*pac)[1];
						rv[2] = i;
						rv[3] = i + 1;
						//rv[4] = distance((*pac), rv);
						return rv;					
					}
				}
			}
		}
	}

	vector<6> projectModFood(vector<6> pac, char dir, Map* map, int n, int f) { // find the next node in the given direction, returns the node and distance and that value of the food in those nodes
		vector<6> rv;
		rv[0] = -1;
		rv[4] = 2 + n;
		rv[5] = f;
		switch(dir) {
			case RIGHT: {
				for(short i = pac[1] + 1; i < 28; i++) {
					rv[4] += 1;
					rv[5] += isFood(pac[2], i) ? 1 : 0; 
					if(isNode(pac[2], i)) {
						rv[0] = i;
						rv[1] = i + 1;
						rv[2] = (pac)[2];
						rv[3] = (pac)[3];
						//rv[4] =  distance(pac, rv);
						return rv;
					}
				}

			}
			case LEFT: {
				for(short i = pac[0] - 1; i >= 1; i--) {
					rv[4] += 1;
					rv[5] += isFood((pac)[2], i) ? 1 : 0; 
					if(isNode(pac[2], i)) {
						rv[0] = i - 1;
						rv[1] = i;
						rv[2] = pac[2];
						rv[3] = pac[3];
						//rv[4] = distance(pac, rv);
						return rv;
					}
				}
			}
			case UP: 
			{
				for(short i = (pac)[2] - 1; i >= 1; i--) {
					rv[4] += 1;
					rv[5] += isFood(i, (pac)[0]) ? 1 : 0; 
					if(isNode(i, pac[0])) {
						rv[0] = pac[0];
						rv[1] = pac[1];
						rv[2] = i - 1;
						rv[3] = i;
						//rv[4] = distance(pac, rv);
						return rv;
					}
				}
			}
			case DOWN: 
			{
				for(short i = (pac)[3] + 1; i < 31; i++) {
					rv[4] += 1;
					rv[5] += isFood(i, (pac)[0]) ? 1 : 0; 
					if(isNode(i, (pac)[0])) {
						rv[0] = (pac)[0];
						rv[1] = (pac)[1];
						rv[2] = i;
						rv[3] = i + 1;
						//rv[4] = distance(pac, rv);
						return rv;					
					}
				}
			}
		}
	}

	short dist[32][29];

	#define isTarget(a, t) (a[0] == t[0] && a[1] == t[1] && a[2] == t[2] && a[3] == t[3])
	#define visited(n) (dist[n[2]][n[0]] != -1)
	#define setVisited(n) dist[n[2]][n[0]] = n[4]
	#define val(n) dist[n[2]][n[0]]
	#define valAd(n) dist[n[2]][n[1]]
	#define withinBB(n) (n[0] > bb[0] && n[1] < bb[1] && n[2] > bb[2] && n[3] < bb[3])

	int shortestPathD(vector<5> start, vector<5> t, Map* map) {
		memset(dist, -1, sizeof(dist[0][0]) * 32 * 29);
		Queue<vector<5>> q;
		val(start) = 0;

		start[4] = 0;

		vector<4> bb;
		bb[0] = min(start[0], t[0]) - 7;
		bb[1] = max(start[1], t[1]) + 7;
		bb[2] = min(start[2], t[2]) - 7;
		bb[3] = max(start[3], t[3]) + 7;

		q.push(start);
		vector<2> dir;
		short d = 1293;
		while(q.size > 0) {
			const vector<5> &temp = q.pop();
		 	for(int i = 0; i < 4; i++) {
		 		dir[0] = z[i];
		 		dir[1] = z2[i];
		 		vector<5> n = projectMod(temp, dir, map, val(temp));
		 		if(n[0] < 0 || !withinBB(n)) continue;
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

	char dirs[4] = { UP,  RIGHT, LEFT, DOWN };
	vector<2> shortestPathDWithFood(vector<6> start, vector<6> t, Map* map) {
		memset(dist, -1, sizeof(dist[0][0]) * 32 * 29);
		Queue<vector<6>> q;
		val(start) = 0;

		start[4] = 0;

		vector<4> bb;
		bb[0] = min(start[0], t[0]) - 7;
		bb[1] = max(start[1], t[1]) + 7;
		bb[2] = min(start[2], t[2]) - 7;
		bb[3] = max(start[3], t[3]) + 7;

		vector<2> r;

		q.push(start);
		short d = 1293;
		while(q.size > 0) {
			const vector<6> &temp = q.pop();
		 	for(int i = 0; i < 4; i++) {
		 		vector<6> n = projectModFood(temp, dirs[i], map, val(temp), valAd(temp));
		 		if(n[0] < 0 || !withinBB(n)) continue;
	 			if(!visited(n)) {
	 				setVisited(n);
	 				if(isTarget(n, t)) {
	 					d = n[4];
	 					r[1] = n[5];
	 				}
	 				else {
	 					q.push(n);
	 				}
	 			}
	 			else {
	 				if(n[4] < val(n)) {
	 					val(n) = n[4];
	 					valAd(n) = n[5];
	 					q.push(n);
	 				}
	 				if(isTarget(n, t)) {
	 					d = val(n);
	 					r[1] = valAd(n);
	 				}
	 			}
	  		}
		}
		r[0] = d;
		return r;
	} 	 	
};

#endif