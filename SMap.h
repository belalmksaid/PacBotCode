#ifndef SMAP
#define SMAP

#include "HashMap.h"
#include "Pos.h"
#include "Arduino.h"

class Edge;

class Node {
public:
	Edge** edges;
	int x1, x2, y1, y2;
	short n = 0;
	bool visited = false;

	double f, g, h;
	double cost;
	Node* parent = NULL;

	Node(int _x1, int _x2, int _y1, int _y2, short _n) {
		x1 = _x1;
		x2 = _x2;
		y1 = _y1;
		y2 = _y2;
		n = _n;
		edges = new Edge*[_n];
	}
	// void reset() {
	// 	visited = false;
	// 	if(n >= 1 && edges[0]->visited) {
	// 		edges[0]->reset();
	// 	}
	// 	if(n >= 2 && edges[1]->visited) {
	// 		edges[1]->reset();
	// 	}
	// 	if(n >= 3 && edges[2]->visited) {
	// 		edges[2]->reset();
	// 	}
	// }

	int getHash() {
		return x1 * 1000000 +  10000 * x2 + y1 * 100 +  y2;	
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

	void printNEdges() {
		Serial.println(n);
	}

	// void traverse() {
	// 	visited = true;
	// 	Serial.print("Node: ");
	// 	print();
	// 	Serial.print("There are ");
	// 	Serial.print(n);
	// 	Serial.println(" edges");
	// 	if(n >= 1) {
	// 		edges[0]->print();
	// 	}
	// 	if(n >= 2) {
	// 		edges[1]->print();
	// 	}
	// 	if(n >= 3 ) {
	// 		edges[2]->print();
	// 	}

	// 	if(n >= 1) {
	// 		edges[0]->traverse();
	// 	}
	// 	if(n >= 2) {
	// 		edges[1]->traverse();
	// 	}
	// 	if(n >= 3 ) {
	// 		edges[2]->traverse();
	// 	}
	// }

	bool operator==(const Node& a) {
		return a.x1 == (*this).x1 && a.x2 == (*this).x2 && a.y1 == (*this).y1 && a.y2 == (*this).y2; 
	}

	bool operator!=(const Node& a) {
		return a.x1 != (*this).x1 || a.x2 != (*this).x2 || a.y1 != (*this).y1 || a.y2 != (*this).y2; 
	}
};

class Edge {
public:
	Node** nodes;
	int x1, x2, y1, y2;
	short n = 0;

	bool visited = false;

	double length = 0;

	// void reset() {
	// 	visited = false;
	// 	if(n >= 1 && nodes[0]->visited) {
	// 		nodes[0]->reset();
	// 	}
	// 	if(n >= 2 && nodes[1]->visited) {
	// 		nodes[1]->reset();
	// 	}
	// }

	Edge(int _x1, int _x2, int _y1, int _y2, short _n) {
		x1 = _x1;
		x2 = _x2;
		y1 = _y1;
		y2 = _y2;
		n = _n;
		nodes = new Node*[_n];
	}

	// void traverse() {
	// 	if(n >= 1 && !nodes[0]->visited) {
	// 		nodes[0]->traverse();
	// 	}
	// 	if(n >= 2 && !nodes[1]->visited) {
	// 		nodes[1]->traverse();
	// 	}
	// }

	void print() {
		Serial.print(x1);
		Serial.print("\t");
		Serial.print(x2);
		Serial.print("\t");
		Serial.print(y1);
		Serial.print("\t");
		Serial.println(y2);
	}

};

class SMap {
public:
	HashType<int, Node*> hashRawArray[64];
	HashMap<int, Node*> hashMap;

	Node* cNode;
	Edge* cEdge;

	SMap() : hashMap(hashRawArray, 64) {
		createSolutionMap();
	}

	void createSolutionMap() { // Creates the graph for the map with each node being a decision point, each node has a unqiue identifier with the equation x1 * 1000000 + x2 * 10000 + y1 * 100 +  y2
		Node *n1020102 = new Node(1, 2, 1, 2, 2); //Node (1, 2, 1, 2)
		hashMap[0](1020102, n1020102);
		Node *n6070102 = new Node(6, 7, 1, 2, 3); //Node (6, 7, 1, 2)
		hashMap[1](6070102, n6070102);
		Node *n12130102 = new Node(12, 13, 1, 2, 2); //Node (12, 13, 1, 2)
		hashMap[2](12130102, n12130102);
		Node *n15160102 = new Node(15, 16, 1, 2, 2); //Node (15, 16, 1, 2)
		hashMap[3](15160102, n15160102);
		Node *n21220102 = new Node(21, 22, 1, 2, 3); //Node (21, 22, 1, 2)
		hashMap[4](21220102, n21220102);
		Node *n26270102 = new Node(26, 27, 1, 2, 2); //Node (26, 27, 1, 2)
		hashMap[5](26270102, n26270102);
		Node *n1020506 = new Node(1, 2, 5, 6, 3); //Node (1, 2, 5, 6)
		hashMap[6](1020506, n1020506);
		Node *n6070506 = new Node(6, 7, 5, 6, 4); //Node (6, 7, 5, 6)
		hashMap[7](6070506, n6070506);
		Node *n9100506 = new Node(9, 10, 5, 6, 3); //Node (9, 10, 5, 6)
		hashMap[8](9100506, n9100506);
		Node *n12130506 = new Node(12, 13, 5, 6, 3); //Node (12, 13, 5, 6)
		hashMap[9](12130506, n12130506);
		Node *n15160506 = new Node(15, 16, 5, 6, 3); //Node (15, 16, 5, 6)
		hashMap[10](15160506, n15160506);
		Node *n18190506 = new Node(18, 19, 5, 6, 3); //Node (18, 19, 5, 6)
		hashMap[11](18190506, n18190506);
		Node *n21220506 = new Node(21, 22, 5, 6, 4); //Node (21, 22, 5, 6)
		hashMap[12](21220506, n21220506);
		Node *n26270506 = new Node(26, 27, 5, 6, 3); //Node (26, 27, 5, 6)
		hashMap[13](26270506, n26270506);
		Node *n1020809 = new Node(1, 2, 8, 9, 2); //Node (1, 2, 8, 9)
		hashMap[14](1020809, n1020809);
		Node *n6070809 = new Node(6, 7, 8, 9, 3); //Node (6, 7, 8, 9)
		hashMap[15](6070809, n6070809);
		Node *n9100809 = new Node(9, 10, 8, 9, 2); //Node (9, 10, 8, 9)
		hashMap[16](9100809, n9100809);
		Node *n12130809 = new Node(12, 13, 8, 9, 2); //Node (12, 13, 8, 9)
		hashMap[17](12130809, n12130809);
		Node *n15160809 = new Node(15, 16, 8, 9, 2); //Node (15, 16, 8, 9)
		hashMap[18](15160809, n15160809);
		Node *n18190809 = new Node(18, 19, 8, 9, 2); //Node (18, 19, 8, 9)
		hashMap[19](18190809, n18190809);
		Node *n21220809 = new Node(21, 22, 8, 9, 3); //Node (21, 22, 8, 9)
		hashMap[20](21220809, n21220809);
		Node *n26270809 = new Node(26, 27, 8, 9, 2); //Node (26, 27, 8, 9)
		hashMap[21](26270809, n26270809);
		Node *n9101112 = new Node(9, 10, 11, 12, 2); //Node (9, 10, 11, 12)
		hashMap[22](9101112, n9101112);
		Node *n12131112 = new Node(12, 13, 11, 12, 3); //Node (12, 13, 11, 12)
		hashMap[23](12131112, n12131112);
		Node *n15161112 = new Node(15, 16, 11, 12, 3); //Node (15, 16, 11, 12)
		hashMap[24](15161112, n15161112);
		Node *n18191112 = new Node(18, 19, 11, 12, 2); //Node (18, 19, 11, 12)
		hashMap[25](18191112, n18191112);
		Node *n6071415 = new Node(6, 7, 14, 15, 4); //Node (6, 7, 14, 15)
		hashMap[26](6071415, n6071415);
		Node *n9101415 = new Node(9, 10, 14, 15, 3); //Node (9, 10, 14, 15)
		hashMap[27](9101415, n9101415);
		Node *n18191415 = new Node(18, 19, 14, 15, 3); //Node (18, 19, 14, 15)
		hashMap[28](18191415, n18191415);
		Node *n21221415 = new Node(21, 22, 14, 15, 4); //Node (21, 22, 14, 15)
		hashMap[29](21221415, n21221415);
		Node *n9101718 = new Node(9, 10, 17, 18, 3); //Node (9, 10, 17, 18)
		hashMap[30](9101718, n9101718);
		Node *n18191718 = new Node(18, 19, 17, 18, 3); //Node (18, 19, 17, 18)
		hashMap[31](18191718, n18191718);
		Node *n1022021 = new Node(1, 2, 20, 21, 2); //Node (1, 2, 20, 21)
		hashMap[32](1022021, n1022021);
		Node *n6072021 = new Node(6, 7, 20, 21, 4); //Node (6, 7, 20, 21)
		hashMap[33](6072021, n6072021);
		Node *n9102021 = new Node(9, 10, 20, 21, 3); //Node (9, 10, 20, 21)
		hashMap[34](9102021, n9102021);
		Node *n12132021 = new Node(12, 13, 20, 21, 2); //Node (12, 13, 20, 21)
		hashMap[35](12132021, n12132021);
		Node *n15162021 = new Node(15, 16, 20, 21, 2); //Node (15, 16, 20, 21)
		hashMap[36](15162021, n15162021);
		Node *n18192021 = new Node(18, 19, 20, 21, 3); //Node (18, 19, 20, 21)
		hashMap[37](18192021, n18192021);
		Node *n21222021 = new Node(21, 22, 20, 21, 4); //Node (21, 22, 20, 21)
		hashMap[38](21222021, n21222021);
		Node *n26272021 = new Node(26, 27, 20, 21, 2); //Node (26, 27, 20, 21)
		hashMap[39](26272021, n26272021);
		Node *n1022324 = new Node(1, 2, 23, 24, 1); //Node (1, 2, 23, 24)
		hashMap[40](1022324, n1022324);
		Node *n3042324 = new Node(3, 4, 23, 24, 1); //Node (3, 4, 23, 24)
		hashMap[41](3042324, n3042324);
		Node *n6072324 = new Node(6, 7, 23, 24, 3); //Node (6, 7, 23, 24)
		hashMap[42](6072324, n6072324);
		Node *n9102324 = new Node(9, 10, 23, 24, 3); //Node (9, 10, 23, 24)
		hashMap[43](9102324, n9102324);
		Node *n12132324 = new Node(12, 13, 23, 24, 3); //Node (12, 13, 23, 24)
		hashMap[44](12132324, n12132324);
		Node *n15162324 = new Node(15, 16, 23, 24, 3); //Node (15, 16, 23, 24)
		hashMap[45](15162324, n15162324);
		Node *n18192324 = new Node(18, 19, 23, 24, 3); //Node (18, 19, 23, 24)
		hashMap[46](18192324, n18192324);
		Node *n21222324 = new Node(21, 22, 23, 24, 3); //Node (21, 22, 23, 24)
		hashMap[47](21222324, n21222324);
		Node *n24252324 = new Node(24, 25, 23, 24, 1); //Node (24, 25, 23, 24)
		hashMap[48](24252324, n24252324);
		Node *n26272324 = new Node(26, 27, 23, 24, 1); //Node (26, 27, 23, 24)
		hashMap[49](26272324, n26272324);
		Node *n1022627 = new Node(1, 2, 26, 27, 1); //Node (1, 2, 26, 27)
		hashMap[50](1022627, n1022627);
		Node *n3042627 = new Node(3, 4, 26, 27, 2); //Node (3, 4, 26, 27)
		hashMap[51](3042627, n3042627);
		Node *n6072627 = new Node(6, 7, 26, 27, 2); //Node (6, 7, 26, 27)
		hashMap[52](6072627, n6072627);
		Node *n9102627 = new Node(9, 10, 26, 27, 2); //Node (9, 10, 26, 27)
		hashMap[53](9102627, n9102627);
		Node *n12132627 = new Node(12, 13, 26, 27, 2); //Node (12, 13, 26, 27)
		hashMap[54](12132627, n12132627);
		Node *n15162627 = new Node(15, 16, 26, 27, 2); //Node (15, 16, 26, 27)
		hashMap[55](15162627, n15162627);
		Node *n18192627 = new Node(18, 19, 26, 27, 2); //Node (18, 19, 26, 27)
		hashMap[56](18192627, n18192627);
		Node *n21222627 = new Node(21, 22, 26, 27, 2); //Node (21, 22, 26, 27)
		hashMap[57](21222627, n21222627);
		Node *n24252627 = new Node(24, 25, 26, 27, 2); //Node (24, 25, 26, 27)
		hashMap[58](24252627, n24252627);
		Node *n26272627 = new Node(26, 27, 26, 27, 1); //Node (26, 27, 26, 27)
		hashMap[59](26272627, n26272627);
		Node *n1022930 = new Node(1, 2, 29, 30, 2); //Node (1, 2, 29, 30)
		hashMap[60](1022930, n1022930);
		Node *n12132930 = new Node(12, 13, 29, 30, 3); //Node (12, 13, 29, 30)
		hashMap[61](12132930, n12132930);
		Node *n15162930 = new Node(15, 16, 29, 30, 3); //Node (15, 16, 29, 30)
		hashMap[62](15162930, n15162930);
		Node *n26272930 = new Node(26, 27, 29, 30, 2); //Node (26, 27, 29, 30)
		hashMap[63](26272930, n26272930);



		Edge *e3004_10002 = new Edge(1, 2, 3, 4, 2);
		e3004_10002->length = 7;
		//Connects Node (1, 2, 1, 2)
		e3004_10002->nodes[0] = n1020102;
		//Connects Node (1, 2, 5, 6)
		e3004_10002->nodes[1] = n1020506;

		Edge *e1002_30005 = new Edge(3, 5, 1, 2, 2);
		e1002_30005->length = 10.5;
		//Connects Node (1, 2, 1, 2)
		e1002_30005->nodes[0] = n1020102;
		//Connects Node (6, 7, 1, 2)
		e1002_30005->nodes[1] = n6070102;

		Edge *e3004_60007 = new Edge(6, 7, 3, 4, 2);
		e3004_60007->length = 7;
		//Connects Node (6, 7, 1, 2)
		e3004_60007->nodes[0] = n6070102;
		//Connects Node (6, 7, 5, 6)
		e3004_60007->nodes[1] = n6070506;

		Edge *e1002_800011 = new Edge(8, 11, 1, 2, 2);
		e1002_800011->length = 14;
		//Connects Node (6, 7, 1, 2)
		e1002_800011->nodes[0] = n6070102;
		//Connects Node (12, 13, 1, 2)
		e1002_800011->nodes[1] = n12130102;

		Edge *e3004_1200013 = new Edge(12, 13, 3, 4, 2);
		e3004_1200013->length = 7;
		//Connects Node (12, 13, 1, 2)
		e3004_1200013->nodes[0] = n12130102;
		//Connects Node (12, 13, 5, 6)
		e3004_1200013->nodes[1] = n12130506;

		Edge *e3004_1500016 = new Edge(15, 16, 3, 4, 2);
		e3004_1500016->length = 7;
		//Connects Node (15, 16, 1, 2)
		e3004_1500016->nodes[0] = n15160102;
		//Connects Node (15, 16, 5, 6)
		e3004_1500016->nodes[1] = n15160506;

		Edge *e1002_1700020 = new Edge(17, 20, 1, 2, 2);
		e1002_1700020->length = 14;
		//Connects Node (15, 16, 1, 2)
		e1002_1700020->nodes[0] = n15160102;
		//Connects Node (21, 22, 1, 2)
		e1002_1700020->nodes[1] = n21220102;

		Edge *e3004_2100022 = new Edge(21, 22, 3, 4, 2);
		e3004_2100022->length = 7;
		//Connects Node (21, 22, 1, 2)
		e3004_2100022->nodes[0] = n21220102;
		//Connects Node (21, 22, 5, 6)
		e3004_2100022->nodes[1] = n21220506;

		Edge *e1002_2300025 = new Edge(23, 25, 1, 2, 2);
		e1002_2300025->length = 10.5;
		//Connects Node (21, 22, 1, 2)
		e1002_2300025->nodes[0] = n21220102;
		//Connects Node (26, 27, 1, 2)
		e1002_2300025->nodes[1] = n26270102;

		Edge *e3004_2600027 = new Edge(26, 27, 3, 4, 2);
		e3004_2600027->length = 7;
		//Connects Node (26, 27, 1, 2)
		e3004_2600027->nodes[0] = n26270102;
		//Connects Node (26, 27, 5, 6)
		e3004_2600027->nodes[1] = n26270506;

		Edge *e7007_10002 = new Edge(1, 2, 7, 7, 2);
		e7007_10002->length = 3.5;
		//Connects Node (1, 2, 5, 6)
		e7007_10002->nodes[0] = n1020506;
		//Connects Node (1, 2, 8, 9)
		e7007_10002->nodes[1] = n1020809;

		Edge *e5006_30005 = new Edge(3, 5, 5, 6, 2);
		e5006_30005->length = 10.5;
		//Connects Node (1, 2, 5, 6)
		e5006_30005->nodes[0] = n1020506;
		//Connects Node (6, 7, 5, 6)
		e5006_30005->nodes[1] = n6070506;

		Edge *e7007_60007 = new Edge(6, 7, 7, 7, 2);
		e7007_60007->length = 3.5;
		//Connects Node (6, 7, 5, 6)
		e7007_60007->nodes[0] = n6070506;
		//Connects Node (6, 7, 8, 9)
		e7007_60007->nodes[1] = n6070809;

		Edge *e5006_80008 = new Edge(8, 8, 5, 6, 2);
		e5006_80008->length = 3.5;
		//Connects Node (6, 7, 5, 6)
		e5006_80008->nodes[0] = n6070506;
		//Connects Node (9, 10, 5, 6)
		e5006_80008->nodes[1] = n9100506;

		Edge *e7007_900010 = new Edge(9, 10, 7, 7, 2);
		e7007_900010->length = 3.5;
		//Connects Node (9, 10, 5, 6)
		e7007_900010->nodes[0] = n9100506;
		//Connects Node (9, 10, 8, 9)
		e7007_900010->nodes[1] = n9100809;

		Edge *e5006_1100011 = new Edge(11, 11, 5, 6, 2);
		e5006_1100011->length = 3.5;
		//Connects Node (9, 10, 5, 6)
		e5006_1100011->nodes[0] = n9100506;
		//Connects Node (12, 13, 5, 6)
		e5006_1100011->nodes[1] = n12130506;

		Edge *e5006_1400014 = new Edge(14, 14, 5, 6, 2);
		e5006_1400014->length = 3.5;
		//Connects Node (12, 13, 5, 6)
		e5006_1400014->nodes[0] = n12130506;
		//Connects Node (15, 16, 5, 6)
		e5006_1400014->nodes[1] = n15160506;

		Edge *e5006_1700017 = new Edge(17, 17, 5, 6, 2);
		e5006_1700017->length = 3.5;
		//Connects Node (15, 16, 5, 6)
		e5006_1700017->nodes[0] = n15160506;
		//Connects Node (18, 19, 5, 6)
		e5006_1700017->nodes[1] = n18190506;

		Edge *e7007_1800019 = new Edge(18, 19, 7, 7, 2);
		e7007_1800019->length = 3.5;
		//Connects Node (18, 19, 5, 6)
		e7007_1800019->nodes[0] = n18190506;
		//Connects Node (18, 19, 8, 9)
		e7007_1800019->nodes[1] = n18190809;

		Edge *e5006_2000020 = new Edge(20, 20, 5, 6, 2);
		e5006_2000020->length = 3.5;
		//Connects Node (18, 19, 5, 6)
		e5006_2000020->nodes[0] = n18190506;
		//Connects Node (21, 22, 5, 6)
		e5006_2000020->nodes[1] = n21220506;

		Edge *e7007_2100022 = new Edge(21, 22, 7, 7, 2);
		e7007_2100022->length = 3.5;
		//Connects Node (21, 22, 5, 6)
		e7007_2100022->nodes[0] = n21220506;
		//Connects Node (21, 22, 8, 9)
		e7007_2100022->nodes[1] = n21220809;

		Edge *e5006_2300025 = new Edge(23, 25, 5, 6, 2);
		e5006_2300025->length = 10.5;
		//Connects Node (21, 22, 5, 6)
		e5006_2300025->nodes[0] = n21220506;
		//Connects Node (26, 27, 5, 6)
		e5006_2300025->nodes[1] = n26270506;

		Edge *e7007_2600027 = new Edge(26, 27, 7, 7, 2);
		e7007_2600027->length = 3.5;
		//Connects Node (26, 27, 5, 6)
		e7007_2600027->nodes[0] = n26270506;
		//Connects Node (26, 27, 8, 9)
		e7007_2600027->nodes[1] = n26270809;

		Edge *e8009_30005 = new Edge(3, 5, 8, 9, 2);
		e8009_30005->length = 10.5;
		//Connects Node (1, 2, 8, 9)
		e8009_30005->nodes[0] = n1020809;
		//Connects Node (6, 7, 8, 9)
		e8009_30005->nodes[1] = n6070809;

		Edge *e10013_60007 = new Edge(6, 7, 10, 13, 2);
		e10013_60007->length = 14;
		//Connects Node (6, 7, 8, 9)
		e10013_60007->nodes[0] = n6070809;
		//Connects Node (6, 7, 14, 15)
		e10013_60007->nodes[1] = n6071415;

		Edge *e8009_1100011 = new Edge(11, 11, 8, 9, 2);
		e8009_1100011->length = 3.5;
		//Connects Node (9, 10, 8, 9)
		e8009_1100011->nodes[0] = n9100809;
		//Connects Node (12, 13, 8, 9)
		e8009_1100011->nodes[1] = n12130809;

		Edge *e10010_1200013 = new Edge(12, 13, 10, 10, 2);
		e10010_1200013->length = 3.5;
		//Connects Node (12, 13, 8, 9)
		e10010_1200013->nodes[0] = n12130809;
		//Connects Node (12, 13, 11, 12)
		e10010_1200013->nodes[1] = n12131112;

		Edge *e10010_1500016 = new Edge(15, 16, 10, 10, 2);
		e10010_1500016->length = 3.5;
		//Connects Node (15, 16, 8, 9)
		e10010_1500016->nodes[0] = n15160809;
		//Connects Node (15, 16, 11, 12)
		e10010_1500016->nodes[1] = n15161112;

		Edge *e8009_1700017 = new Edge(17, 17, 8, 9, 2);
		e8009_1700017->length = 3.5;
		//Connects Node (15, 16, 8, 9)
		e8009_1700017->nodes[0] = n15160809;
		//Connects Node (18, 19, 8, 9)
		e8009_1700017->nodes[1] = n18190809;

		Edge *e10013_2100022 = new Edge(21, 22, 10, 13, 2);
		e10013_2100022->length = 14;
		//Connects Node (21, 22, 8, 9)
		e10013_2100022->nodes[0] = n21220809;
		//Connects Node (21, 22, 14, 15)
		e10013_2100022->nodes[1] = n21221415;

		Edge *e8009_2300025 = new Edge(23, 25, 8, 9, 2);
		e8009_2300025->length = 10.5;
		//Connects Node (21, 22, 8, 9)
		e8009_2300025->nodes[0] = n21220809;
		//Connects Node (26, 27, 8, 9)
		e8009_2300025->nodes[1] = n26270809;

		Edge *e13013_900010 = new Edge(9, 10, 13, 13, 2);
		e13013_900010->length = 3.5;
		//Connects Node (9, 10, 11, 12)
		e13013_900010->nodes[0] = n9101112;
		//Connects Node (9, 10, 14, 15)
		e13013_900010->nodes[1] = n9101415;

		Edge *e11012_1100011 = new Edge(11, 11, 11, 12, 2);
		e11012_1100011->length = 3.5;
		//Connects Node (9, 10, 11, 12)
		e11012_1100011->nodes[0] = n9101112;
		//Connects Node (12, 13, 11, 12)
		e11012_1100011->nodes[1] = n12131112;

		Edge *e11012_1400014 = new Edge(14, 14, 11, 12, 2);
		e11012_1400014->length = 3.5;
		//Connects Node (12, 13, 11, 12)
		e11012_1400014->nodes[0] = n12131112;
		//Connects Node (15, 16, 11, 12)
		e11012_1400014->nodes[1] = n15161112;

		Edge *e11012_1700017 = new Edge(17, 17, 11, 12, 2);
		e11012_1700017->length = 3.5;
		//Connects Node (15, 16, 11, 12)
		e11012_1700017->nodes[0] = n15161112;
		//Connects Node (18, 19, 11, 12)
		e11012_1700017->nodes[1] = n18191112;

		Edge *e13013_1800019 = new Edge(18, 19, 13, 13, 2);
		e13013_1800019->length = 3.5;
		//Connects Node (18, 19, 11, 12)
		e13013_1800019->nodes[0] = n18191112;
		//Connects Node (18, 19, 14, 15)
		e13013_1800019->nodes[1] = n18191415;

		Edge *e16019_60007 = new Edge(6, 7, 16, 19, 2);
		e16019_60007->length = 14;
		//Connects Node (6, 7, 14, 15)
		e16019_60007->nodes[0] = n6071415;
		//Connects Node (6, 7, 20, 21)
		e16019_60007->nodes[1] = n6072021;

		Edge *e14015_10005 = new Edge(1, 5, 14, 15, 1);
		e14015_10005->length = 17.5;
		//Connects Node (6, 7, 14, 15)
		e14015_10005->nodes[0] = n6071415;

		Edge *e14015_80008 = new Edge(8, 8, 14, 15, 2);
		e14015_80008->length = 3.5;
		//Connects Node (6, 7, 14, 15)
		e14015_80008->nodes[0] = n6071415;
		//Connects Node (9, 10, 14, 15)
		e14015_80008->nodes[1] = n9101415;

		Edge *e16016_900010 = new Edge(9, 10, 16, 16, 2);
		e16016_900010->length = 3.5;
		//Connects Node (9, 10, 14, 15)
		e16016_900010->nodes[0] = n9101415;
		//Connects Node (9, 10, 17, 18)
		e16016_900010->nodes[1] = n9101718;

		Edge *e16016_1800019 = new Edge(18, 19, 16, 16, 2);
		e16016_1800019->length = 3.5;
		//Connects Node (18, 19, 14, 15)
		e16016_1800019->nodes[0] = n18191415;
		//Connects Node (18, 19, 17, 18)
		e16016_1800019->nodes[1] = n18191718;

		Edge *e14015_2000020 = new Edge(20, 20, 14, 15, 2);
		e14015_2000020->length = 3.5;
		//Connects Node (18, 19, 14, 15)
		e14015_2000020->nodes[0] = n18191415;
		//Connects Node (21, 22, 14, 15)
		e14015_2000020->nodes[1] = n21221415;

		Edge *e16019_2100022 = new Edge(21, 22, 16, 19, 2);
		e16019_2100022->length = 14;
		//Connects Node (21, 22, 14, 15)
		e16019_2100022->nodes[0] = n21221415;
		//Connects Node (21, 22, 20, 21)
		e16019_2100022->nodes[1] = n21222021;

		Edge *e14015_2300027 = new Edge(23, 27, 14, 15, 1);
		e14015_2300027->length = 17.5;
		//Connects Node (21, 22, 14, 15)
		e14015_2300027->nodes[0] = n21221415;

		Edge *e19019_900010 = new Edge(9, 10, 19, 19, 2);
		e19019_900010->length = 3.5;
		//Connects Node (9, 10, 17, 18)
		e19019_900010->nodes[0] = n9101718;
		//Connects Node (9, 10, 20, 21)
		e19019_900010->nodes[1] = n9102021;

		Edge *e17018_1100017 = new Edge(11, 17, 17, 18, 2);
		e17018_1100017->length = 24.5;
		//Connects Node (9, 10, 17, 18)
		e17018_1100017->nodes[0] = n9101718;
		//Connects Node (18, 19, 17, 18)
		e17018_1100017->nodes[1] = n18191718;

		Edge *e19019_1800019 = new Edge(18, 19, 19, 19, 2);
		e19019_1800019->length = 3.5;
		//Connects Node (18, 19, 17, 18)
		e19019_1800019->nodes[0] = n18191718;
		//Connects Node (18, 19, 20, 21)
		e19019_1800019->nodes[1] = n18192021;

		Edge *e22022_10002 = new Edge(1, 2, 22, 22, 2);
		e22022_10002->length = 3.5;
		//Connects Node (1, 2, 20, 21)
		e22022_10002->nodes[0] = n1022021;
		//Connects Node (1, 2, 23, 24)
		e22022_10002->nodes[1] = n1022324;

		Edge *e20021_30005 = new Edge(3, 5, 20, 21, 2);
		e20021_30005->length = 10.5;
		//Connects Node (1, 2, 20, 21)
		e20021_30005->nodes[0] = n1022021;
		//Connects Node (6, 7, 20, 21)
		e20021_30005->nodes[1] = n6072021;

		Edge *e22022_60007 = new Edge(6, 7, 22, 22, 2);
		e22022_60007->length = 3.5;
		//Connects Node (6, 7, 20, 21)
		e22022_60007->nodes[0] = n6072021;
		//Connects Node (6, 7, 23, 24)
		e22022_60007->nodes[1] = n6072324;

		Edge *e20021_80008 = new Edge(8, 8, 20, 21, 2);
		e20021_80008->length = 3.5;
		//Connects Node (6, 7, 20, 21)
		e20021_80008->nodes[0] = n6072021;
		//Connects Node (9, 10, 20, 21)
		e20021_80008->nodes[1] = n9102021;

		Edge *e20021_1100011 = new Edge(11, 11, 20, 21, 2);
		e20021_1100011->length = 3.5;
		//Connects Node (9, 10, 20, 21)
		e20021_1100011->nodes[0] = n9102021;
		//Connects Node (12, 13, 20, 21)
		e20021_1100011->nodes[1] = n12132021;

		Edge *e22022_1200013 = new Edge(12, 13, 22, 22, 2);
		e22022_1200013->length = 3.5;
		//Connects Node (12, 13, 20, 21)
		e22022_1200013->nodes[0] = n12132021;
		//Connects Node (12, 13, 23, 24)
		e22022_1200013->nodes[1] = n12132324;

		Edge *e22022_1500016 = new Edge(15, 16, 22, 22, 2);
		e22022_1500016->length = 3.5;
		//Connects Node (15, 16, 20, 21)
		e22022_1500016->nodes[0] = n15162021;
		//Connects Node (15, 16, 23, 24)
		e22022_1500016->nodes[1] = n15162324;

		Edge *e20021_1700017 = new Edge(17, 17, 20, 21, 2);
		e20021_1700017->length = 3.5;
		//Connects Node (15, 16, 20, 21)
		e20021_1700017->nodes[0] = n15162021;
		//Connects Node (18, 19, 20, 21)
		e20021_1700017->nodes[1] = n18192021;

		Edge *e20021_2000020 = new Edge(20, 20, 20, 21, 2);
		e20021_2000020->length = 3.5;
		//Connects Node (18, 19, 20, 21)
		e20021_2000020->nodes[0] = n18192021;
		//Connects Node (21, 22, 20, 21)
		e20021_2000020->nodes[1] = n21222021;

		Edge *e22022_2100022 = new Edge(21, 22, 22, 22, 2);
		e22022_2100022->length = 3.5;
		//Connects Node (21, 22, 20, 21)
		e22022_2100022->nodes[0] = n21222021;
		//Connects Node (21, 22, 23, 24)
		e22022_2100022->nodes[1] = n21222324;

		Edge *e20021_2300025 = new Edge(23, 25, 20, 21, 2);
		e20021_2300025->length = 10.5;
		//Connects Node (21, 22, 20, 21)
		e20021_2300025->nodes[0] = n21222021;
		//Connects Node (26, 27, 20, 21)
		e20021_2300025->nodes[1] = n26272021;

		Edge *e22022_2600027 = new Edge(26, 27, 22, 22, 2);
		e22022_2600027->length = 3.5;
		//Connects Node (26, 27, 20, 21)
		e22022_2600027->nodes[0] = n26272021;
		//Connects Node (26, 27, 23, 24)
		e22022_2600027->nodes[1] = n26272324;

		Edge *e25025_30004 = new Edge(3, 4, 25, 25, 2);
		e25025_30004->length = 3.5;
		//Connects Node (3, 4, 23, 24)
		e25025_30004->nodes[0] = n3042324;
		//Connects Node (3, 4, 26, 27)
		e25025_30004->nodes[1] = n3042627;

		Edge *e25025_60007 = new Edge(6, 7, 25, 25, 2);
		e25025_60007->length = 3.5;
		//Connects Node (6, 7, 23, 24)
		e25025_60007->nodes[0] = n6072324;
		//Connects Node (6, 7, 26, 27)
		e25025_60007->nodes[1] = n6072627;

		Edge *e23024_80008 = new Edge(8, 8, 23, 24, 2);
		e23024_80008->length = 3.5;
		//Connects Node (6, 7, 23, 24)
		e23024_80008->nodes[0] = n6072324;
		//Connects Node (9, 10, 23, 24)
		e23024_80008->nodes[1] = n9102324;

		Edge *e25025_900010 = new Edge(9, 10, 25, 25, 2);
		e25025_900010->length = 3.5;
		//Connects Node (9, 10, 23, 24)
		e25025_900010->nodes[0] = n9102324;
		//Connects Node (9, 10, 26, 27)
		e25025_900010->nodes[1] = n9102627;

		Edge *e23024_1100011 = new Edge(11, 11, 23, 24, 2);
		e23024_1100011->length = 3.5;
		//Connects Node (9, 10, 23, 24)
		e23024_1100011->nodes[0] = n9102324;
		//Connects Node (12, 13, 23, 24)
		e23024_1100011->nodes[1] = n12132324;

		Edge *e23024_1400014 = new Edge(14, 14, 23, 24, 2);
		e23024_1400014->length = 3.5;
		//Connects Node (12, 13, 23, 24)
		e23024_1400014->nodes[0] = n12132324;
		//Connects Node (15, 16, 23, 24)
		e23024_1400014->nodes[1] = n15162324;

		Edge *e23024_1700017 = new Edge(17, 17, 23, 24, 2);
		e23024_1700017->length = 3.5;
		//Connects Node (15, 16, 23, 24)
		e23024_1700017->nodes[0] = n15162324;
		//Connects Node (18, 19, 23, 24)
		e23024_1700017->nodes[1] = n18192324;

		Edge *e25025_1800019 = new Edge(18, 19, 25, 25, 2);
		e25025_1800019->length = 3.5;
		//Connects Node (18, 19, 23, 24)
		e25025_1800019->nodes[0] = n18192324;
		//Connects Node (18, 19, 26, 27)
		e25025_1800019->nodes[1] = n18192627;

		Edge *e23024_2000020 = new Edge(20, 20, 23, 24, 2);
		e23024_2000020->length = 3.5;
		//Connects Node (18, 19, 23, 24)
		e23024_2000020->nodes[0] = n18192324;
		//Connects Node (21, 22, 23, 24)
		e23024_2000020->nodes[1] = n21222324;

		Edge *e25025_2100022 = new Edge(21, 22, 25, 25, 2);
		e25025_2100022->length = 3.5;
		//Connects Node (21, 22, 23, 24)
		e25025_2100022->nodes[0] = n21222324;
		//Connects Node (21, 22, 26, 27)
		e25025_2100022->nodes[1] = n21222627;

		Edge *e25025_2400025 = new Edge(24, 25, 25, 25, 2);
		e25025_2400025->length = 3.5;
		//Connects Node (24, 25, 23, 24)
		e25025_2400025->nodes[0] = n24252324;
		//Connects Node (24, 25, 26, 27)
		e25025_2400025->nodes[1] = n24252627;

		Edge *e28028_10002 = new Edge(1, 2, 28, 28, 2);
		e28028_10002->length = 3.5;
		//Connects Node (1, 2, 26, 27)
		e28028_10002->nodes[0] = n1022627;
		//Connects Node (1, 2, 29, 30)
		e28028_10002->nodes[1] = n1022930;

		Edge *e26027_50005 = new Edge(5, 5, 26, 27, 2);
		e26027_50005->length = 3.5;
		//Connects Node (3, 4, 26, 27)
		e26027_50005->nodes[0] = n3042627;
		//Connects Node (6, 7, 26, 27)
		e26027_50005->nodes[1] = n6072627;

		Edge *e26027_1100011 = new Edge(11, 11, 26, 27, 2);
		e26027_1100011->length = 3.5;
		//Connects Node (9, 10, 26, 27)
		e26027_1100011->nodes[0] = n9102627;
		//Connects Node (12, 13, 26, 27)
		e26027_1100011->nodes[1] = n12132627;

		Edge *e28028_1200013 = new Edge(12, 13, 28, 28, 2);
		e28028_1200013->length = 3.5;
		//Connects Node (12, 13, 26, 27)
		e28028_1200013->nodes[0] = n12132627;
		//Connects Node (12, 13, 29, 30)
		e28028_1200013->nodes[1] = n12132930;

		Edge *e28028_1500016 = new Edge(15, 16, 28, 28, 2);
		e28028_1500016->length = 3.5;
		//Connects Node (15, 16, 26, 27)
		e28028_1500016->nodes[0] = n15162627;
		//Connects Node (15, 16, 29, 30)
		e28028_1500016->nodes[1] = n15162930;

		Edge *e26027_1700017 = new Edge(17, 17, 26, 27, 2);
		e26027_1700017->length = 3.5;
		//Connects Node (15, 16, 26, 27)
		e26027_1700017->nodes[0] = n15162627;
		//Connects Node (18, 19, 26, 27)
		e26027_1700017->nodes[1] = n18192627;

		Edge *e26027_2300023 = new Edge(23, 23, 26, 27, 2);
		e26027_2300023->length = 3.5;
		//Connects Node (21, 22, 26, 27)
		e26027_2300023->nodes[0] = n21222627;
		//Connects Node (24, 25, 26, 27)
		e26027_2300023->nodes[1] = n24252627;

		Edge *e28028_2600027 = new Edge(26, 27, 28, 28, 2);
		e28028_2600027->length = 3.5;
		//Connects Node (26, 27, 26, 27)
		e28028_2600027->nodes[0] = n26272627;
		//Connects Node (26, 27, 29, 30)
		e28028_2600027->nodes[1] = n26272930;

		Edge *e29030_300011 = new Edge(3, 11, 29, 30, 2);
		e29030_300011->length = 31.5;
		//Connects Node (1, 2, 29, 30)
		e29030_300011->nodes[0] = n1022930;
		//Connects Node (12, 13, 29, 30)
		e29030_300011->nodes[1] = n12132930;

		Edge *e29030_1400014 = new Edge(14, 14, 29, 30, 2);
		e29030_1400014->length = 3.5;
		//Connects Node (12, 13, 29, 30)
		e29030_1400014->nodes[0] = n12132930;
		//Connects Node (15, 16, 29, 30)
		e29030_1400014->nodes[1] = n15162930;

		Edge *e29030_1700025 = new Edge(17, 25, 29, 30, 2);
		e29030_1700025->length = 31.5;
		//Connects Node (15, 16, 29, 30)
		e29030_1700025->nodes[0] = n15162930;
		//Connects Node (26, 27, 29, 30)
		e29030_1700025->nodes[1] = n26272930;




		n1020102->edges[0] = e3004_10002;
		n1020102->edges[1] = e1002_30005;
		n6070102->edges[0] = e3004_60007;
		n6070102->edges[1] = e1002_30005;
		n6070102->edges[2] = e1002_800011;
		n12130102->edges[0] = e3004_1200013;
		n12130102->edges[1] = e1002_800011;
		n15160102->edges[0] = e3004_1500016;
		n15160102->edges[1] = e1002_1700020;
		n21220102->edges[0] = e3004_2100022;
		n21220102->edges[1] = e1002_1700020;
		n21220102->edges[2] = e1002_2300025;
		n26270102->edges[0] = e3004_2600027;
		n26270102->edges[1] = e1002_2300025;
		n1020506->edges[0] = e3004_10002;
		n1020506->edges[1] = e7007_10002;
		n1020506->edges[2] = e5006_30005;
		n6070506->edges[0] = e3004_60007;
		n6070506->edges[1] = e7007_60007;
		n6070506->edges[2] = e5006_30005;
		n6070506->edges[3] = e5006_80008;
		n9100506->edges[0] = e7007_900010;
		n9100506->edges[1] = e5006_80008;
		n9100506->edges[2] = e5006_1100011;
		n12130506->edges[0] = e3004_1200013;
		n12130506->edges[1] = e5006_1100011;
		n12130506->edges[2] = e5006_1400014;
		n15160506->edges[0] = e3004_1500016;
		n15160506->edges[1] = e5006_1400014;
		n15160506->edges[2] = e5006_1700017;
		n18190506->edges[0] = e7007_1800019;
		n18190506->edges[1] = e5006_1700017;
		n18190506->edges[2] = e5006_2000020;
		n21220506->edges[0] = e3004_2100022;
		n21220506->edges[1] = e7007_2100022;
		n21220506->edges[2] = e5006_2000020;
		n21220506->edges[3] = e5006_2300025;
		n26270506->edges[0] = e3004_2600027;
		n26270506->edges[1] = e7007_2600027;
		n26270506->edges[2] = e5006_2300025;
		n1020809->edges[0] = e7007_10002;
		n1020809->edges[1] = e8009_30005;
		n6070809->edges[0] = e7007_60007;
		n6070809->edges[1] = e10013_60007;
		n6070809->edges[2] = e8009_30005;
		n9100809->edges[0] = e7007_900010;
		n9100809->edges[1] = e8009_1100011;
		n12130809->edges[0] = e10010_1200013;
		n12130809->edges[1] = e8009_1100011;
		n15160809->edges[0] = e10010_1500016;
		n15160809->edges[1] = e8009_1700017;
		n18190809->edges[0] = e7007_1800019;
		n18190809->edges[1] = e8009_1700017;
		n21220809->edges[0] = e7007_2100022;
		n21220809->edges[1] = e10013_2100022;
		n21220809->edges[2] = e8009_2300025;
		n26270809->edges[0] = e7007_2600027;
		n26270809->edges[1] = e8009_2300025;
		n9101112->edges[0] = e13013_900010;
		n9101112->edges[1] = e11012_1100011;
		n12131112->edges[0] = e10010_1200013;
		n12131112->edges[1] = e11012_1100011;
		n12131112->edges[2] = e11012_1400014;
		n15161112->edges[0] = e10010_1500016;
		n15161112->edges[1] = e11012_1400014;
		n15161112->edges[2] = e11012_1700017;
		n18191112->edges[0] = e13013_1800019;
		n18191112->edges[1] = e11012_1700017;
		n6071415->edges[0] = e10013_60007;
		n6071415->edges[1] = e16019_60007;
		n6071415->edges[2] = e14015_10005;
		n6071415->edges[3] = e14015_80008;
		n9101415->edges[0] = e13013_900010;
		n9101415->edges[1] = e16016_900010;
		n9101415->edges[2] = e14015_80008;
		n18191415->edges[0] = e13013_1800019;
		n18191415->edges[1] = e16016_1800019;
		n18191415->edges[2] = e14015_2000020;
		n21221415->edges[0] = e10013_2100022;
		n21221415->edges[1] = e16019_2100022;
		n21221415->edges[2] = e14015_2000020;
		n21221415->edges[3] = e14015_2300027;
		n9101718->edges[0] = e16016_900010;
		n9101718->edges[1] = e19019_900010;
		n9101718->edges[2] = e17018_1100017;
		n18191718->edges[0] = e16016_1800019;
		n18191718->edges[1] = e19019_1800019;
		n18191718->edges[2] = e17018_1100017;
		n1022021->edges[0] = e22022_10002;
		n1022021->edges[1] = e20021_30005;
		n6072021->edges[0] = e16019_60007;
		n6072021->edges[1] = e22022_60007;
		n6072021->edges[2] = e20021_30005;
		n6072021->edges[3] = e20021_80008;
		n9102021->edges[0] = e19019_900010;
		n9102021->edges[1] = e20021_80008;
		n9102021->edges[2] = e20021_1100011;
		n12132021->edges[0] = e22022_1200013;
		n12132021->edges[1] = e20021_1100011;
		n15162021->edges[0] = e22022_1500016;
		n15162021->edges[1] = e20021_1700017;
		n18192021->edges[0] = e19019_1800019;
		n18192021->edges[1] = e20021_1700017;
		n18192021->edges[2] = e20021_2000020;
		n21222021->edges[0] = e16019_2100022;
		n21222021->edges[1] = e22022_2100022;
		n21222021->edges[2] = e20021_2000020;
		n21222021->edges[3] = e20021_2300025;
		n26272021->edges[0] = e22022_2600027;
		n26272021->edges[1] = e20021_2300025;
		n1022324->edges[0] = e22022_10002;
		n3042324->edges[0] = e25025_30004;
		n6072324->edges[0] = e22022_60007;
		n6072324->edges[1] = e25025_60007;
		n6072324->edges[2] = e23024_80008;
		n9102324->edges[0] = e25025_900010;
		n9102324->edges[1] = e23024_80008;
		n9102324->edges[2] = e23024_1100011;
		n12132324->edges[0] = e22022_1200013;
		n12132324->edges[1] = e23024_1100011;
		n12132324->edges[2] = e23024_1400014;
		n15162324->edges[0] = e22022_1500016;
		n15162324->edges[1] = e23024_1400014;
		n15162324->edges[2] = e23024_1700017;
		n18192324->edges[0] = e25025_1800019;
		n18192324->edges[1] = e23024_1700017;
		n18192324->edges[2] = e23024_2000020;
		n21222324->edges[0] = e22022_2100022;
		n21222324->edges[1] = e25025_2100022;
		n21222324->edges[2] = e23024_2000020;
		n24252324->edges[0] = e25025_2400025;
		n26272324->edges[0] = e22022_2600027;
		n1022627->edges[0] = e28028_10002;
		n3042627->edges[0] = e25025_30004;
		n3042627->edges[1] = e26027_50005;
		n6072627->edges[0] = e25025_60007;
		n6072627->edges[1] = e26027_50005;
		n9102627->edges[0] = e25025_900010;
		n9102627->edges[1] = e26027_1100011;
		n12132627->edges[0] = e28028_1200013;
		n12132627->edges[1] = e26027_1100011;
		n15162627->edges[0] = e28028_1500016;
		n15162627->edges[1] = e26027_1700017;
		n18192627->edges[0] = e25025_1800019;
		n18192627->edges[1] = e26027_1700017;
		n21222627->edges[0] = e25025_2100022;
		n21222627->edges[1] = e26027_2300023;
		n24252627->edges[0] = e25025_2400025;
		n24252627->edges[1] = e26027_2300023;
		n26272627->edges[0] = e28028_2600027;
		n1022930->edges[0] = e28028_10002;
		n1022930->edges[1] = e29030_300011;
		n12132930->edges[0] = e28028_1200013;
		n12132930->edges[1] = e29030_300011;
		n12132930->edges[2] = e29030_1400014;
		n15162930->edges[0] = e28028_1500016;
		n15162930->edges[1] = e29030_1400014;
		n15162930->edges[2] = e29030_1700025;
		n26272930->edges[0] = e28028_2600027;
		n26272930->edges[1] = e29030_1700025;
	}

	void updateCurrentNode(Pos* p) {
		cNode = hashMap.getValueOf(p->x1 * 1000000 +  10000 * p->x2 + p->y1 * 100 +  p->y2);
	}

	Node* getNode(Pos* p) {
		return hashMap.getValueOf(p->x1 * 1000000 +  10000 * p->x2 + p->y1 * 100 +  p->y2);
	}

	Node* getNode(int x1, int x2, int y1, int y2) {
		return hashMap.getValueOf(x1 * 1000000 +  10000 * x2 + y1 * 100 +  y2);
	}

	

};


#endif