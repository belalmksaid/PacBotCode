#ifndef Util
#define Util

template<typename T> struct i {
public:	
	i<T>* next = NULL;
	T data;

	void chainDelete() {
		if(next != NULL) {
			next->chainDelete();
			delete next;
		}
	}
};

template<typename T> 
class Queue {
private:
	i<T> *rear, *front;

public:
	int size = 0;

	Queue() {
		rear = NULL;
		front = NULL;
		size = 0;
	}

	~Queue() {
		reset();
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

	void push(T o) {
		size++;

		i<T> *temp = new i<T>;
		temp->data = o;
		temp->next = NULL;

		if(front == NULL) {
			front = temp;
		}
		else {
			rear->next = temp;
		}

		rear = temp;
	}

	T rval;

	T pop() {
		i<T> *temp = new i<T>;

		if(front == NULL) {
			Serial.println("Queue is empty. Something went wrong.");
		}
		else {
			temp = front;
			front = front->next;
			size--;
			rval = temp->data;
			delete temp;
			return rval;
		}
	}

	T current() {
		return front->data;
	}
};

template<typename T> struct t {
public:	
	t<T>* next = NULL;
	t<T>* prev = NULL;
	T data;

	void chainDelete() {
		if(next != NULL) {
			next->chainDelete();
			delete next;
		}
	}
};

template<typename T> class set {
private:
	t<T> *rear;
	t<T> *it;

public:

	~set() {
		reset();
	}

	void reset() {
		if(rear != NULL) {
			rear->chainDelete();
			delete rear;
			rear = NULL;

		}
	}
	
	short size = 0;
	void add(T item) {
		rear->prev = new t<T>;
		rear->prev->data = item;
		rear->prev->next = rear;
		rear = rear->prev;
		size++;

	}

	T pop() {

	}

	bool contains(T item) {
		it = rear;
		if(it == NULL) return false;
		do {
			if(it->data == item)
				return true;
			it = it->next;
		} while(it->next != NULL);

		return false;
	}

	void remove(T item) {
		it = rear;
		if(it == NULL) return;
		do {
			if(it->data == item) {
				if(it->prev != NULL) {
					it->prev->next = it->next;
					
				}
				if(it->next != NULL) {
					it->next->prev = it->prev;
				}
				delete it;
				size--;
				break;
			}
			it = it->next;
		} while(it->next != NULL);
	}

	t<T> *iterator() {
		return rear;
	}
};

template<uint32_t size> class vector
{
private:
	int registers[size];
public:
	~vector() {
	}

	void print() {
		for(int i = 0; i < size; i++) {
			Serial.print(registers[i]);
			Serial.print(" ");
		}
		Serial.println();
	}

	int operator [](int i) const    {return registers[i];}
    int & operator [](int i) {return registers[i];}

    bool operator ==(vector<size> a) {
    	for(int i = 0; i < size; i++) {
    		if(a.registers[i] != (*this).registers[i])
    			return false;
    	}
    	return true;
    }
    bool operator !=(vector<size> a) {
    	return !((*this) == a);
    }
};


#endif