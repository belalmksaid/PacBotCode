#ifndef PATH_
#define PATH_


struct item {
public:
	short data;
	double length;
	item* next;

	void chainDelete() {
		if(next != NULL) {
			next->chainDelete();
			delete next;
		}
	}
};

class Path {
private:
	item *rear, *front;

public:
	double totalLength;
	short n;

	Path() {
		rear = NULL;
		front = NULL;
		n = 0;
		totalLength = 0.0;
	}

	void reset() {
		if(front != NULL) {
			front->chainDelete();
			delete front;
			front = NULL;
			delete rear;
			rear = NULL;

		}
	}

	void push(short o, double l) {
		n++;
		totalLength += l;

		item *temp = new item;
		temp->data = o;
		temp->length = l;

		temp->next = NULL;

		if(front == NULL) {
			front = temp;
		}
		else {
			rear->next = temp;
		}

		rear = temp;
	}

	short rval = 0;

	short pop() {
		item *temp = new item;

		if(front == NULL) {
			return -1;
		}
		else {
			temp = front;
			front = front->next;
			totalLength -= temp->length;
			n--;
			rval = temp->data;
			delete temp;
			return rval;
		}
	}
};

#endif