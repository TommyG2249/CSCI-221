/* HW 17:  classic queue linked list implementation

	Author: Barbara Z. Johnson, faculty of St. Olaf College, and <your name>
	Date: October 24, 2024
	Revised <new data>

	NOTE: this uses a separate file for the Node class!

*/

#include <iostream>
#include "node.hpp"

using namespace std;


// Queue class
class Queue {
private:
    Node* head;
    Node* tail;
	int count;

public:
	// constructor
	// set the head and tail to appropriate values
    Queue() {
		head = nullptr;
    	tail = nullptr;
    	count = 0;
    }

    // destructor .. delete all the nodes and recycle memory
    ~Queue() {
	    while (head != nullptr) {
	    	Node* temp = head->getNext();
	    	delete head;
	    	head = temp;
	    }
    } // destructor


    bool isEmpty() {
    	if (head == nullptr) {
    		return true;
    	}
		return false;  // default to silence the compiler warning.
    }

    // you will need to create a new Node (see the node class in a separate file and use
    // the Node constructor just as we did when both classes were in the same file)
    void enqueue(int val) {
    	if (head == nullptr) {
    		head = new Node(val);
    		tail = head;
    		count++;
    		return;
    	}
    	Node* new_node = new Node(val);
    	tail->setNext(new_node);
    	tail = tail->getNext();
    	count++;
    } // enqueue

    // check to be sure the queue is not already empty!
    // returns the value in the head node, changes where head points,
    //  and deletes the memory used by the formerly first Node
    int dequeue() {
    	if (head == nullptr) {
    		throw out_of_range("Cannot dequeue from an empty queue");
    	}

    	int data;

    	if (head == tail) {
    		data = head->getData();
    		head = nullptr;
    		tail = nullptr;
    		count--;
    		return data;
    	}

    	Node* temp = head->getNext();
    	data = head->getData();
    	delete head;
    	head = temp;
    	temp = nullptr;
    	count--;
        return data;  // default to silence the compiler warning.
    } // dequeue

    // check to be sure the queue is not empty!
    // returns the value in the head node
    // does not change the queue
    int front() {
    	if (head == nullptr) {
    		throw out_of_range("Cannot return front value from an empty queue");
    	}

    	return head->getData(); // default to silence the compiler warning.  REPLACE WITH YOUR CODE
    } // front

    // error message if the queue is empty
    // otherwise, print the whole queue from head to tail
    void printQueue() {
    	if (head == nullptr) {
    		throw out_of_range("Cannot print an empty queue");
    	}

    	Node* temp = head;
    	while (temp != nullptr) {
    		cout << temp->getData() << endl;
    		temp = temp->getNext();
    	} // while
    } // printQueue
};


int main() {

    // Testing queue
    Queue q;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);
    cout << "The queue after 3 additions: " << endl;
    try {q.printQueue();} catch (out_of_range& e) {cerr << "Error: " << e.what() << endl;}
    cout << "The front is: " << q.front() << endl;

	/* trying out exception handling since im doing this late, since the values might not be initialized, i'm setting
	them to -1 in case the try fails */
	int val1 = -1;
	int val2 = -1;
	int val3 = -1;

	try {val1 = q.dequeue();} catch (out_of_range& e) {cerr << "Error: " << e.what() << endl;}
	try {val2 = q.dequeue();} catch (out_of_range& e) {cerr << "Error: " << e.what() << endl;}
	try {val2 = q.dequeue();} catch (out_of_range& e) {cerr << "Error: " << e.what() << endl;}

    cout << val1 << endl;
    cout << val2 << endl;
    cout << val3 << endl;

    q.enqueue(20);
    cout << "The queue after adding 20: " << endl;
    q.printQueue();

	int val4 = -1;

	try {val4 = q.dequeue();} catch (out_of_range& e) {cerr << "Error: " << e.what() << endl;}

    cout << val4 << endl;  // should print -1 for the empty queue

	try {q.front();} catch (out_of_range& e) {cerr << "Error: " << e.what() << endl;}
	q.enqueue(30);
	cout << q.front() << endl;

    return 0;
}
