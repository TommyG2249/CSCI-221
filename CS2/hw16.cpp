//
// Created by Thomas Glennon on 4/14/26.
//

/*
	Author: Barbara Z. Johnson, St. Olaf faculty, and Tommy Glennon
	Date: October 15, 2024
	Revised: April 11, 2026

	STARTER CODE for in-class Day 23 and HW16
	Integer data type for in in-class exercise
	Change the data type stored in the array to string for the homework

*/

#include<iostream>
#include <fstream>
#include <string>
using namespace std;

// this size is small for testing purposes
#define MAX_SIZE 5

// this class is assuming that you will use a circular array and wrap around when
// an index goes beyond the largest index of the array (MAX_SIZE - 1)
class Queue {
  private:
    int front;
    int back;
    int count;
    int capacity;
    string arr[MAX_SIZE];

  public:
    Queue() {
      front = 0;
      count = 0;
      back = MAX_SIZE - 1;
      capacity = MAX_SIZE;
      for (int i = 0; i < MAX_SIZE; i++) {
        arr[i] = "";
      }
    }

  bool isFull() {
      if (count == capacity) {
        cout << "Queue is full!" << endl;
        return true;
      }
      return false;
    }

  bool isEmpty() {
      if (count == 0) {
        cout << "Queue is empty!" << endl;
        return true;
      }
      return false;
    }

// add val to the queue and update class data
// increase the value of the back index BEFORE assigning the value into the array
  bool enqueue(string val) {
      if (isFull()) return false;
      back = (count + front) % capacity;
      arr[back] = val;
      count++;
      return true;
  } // enqueue

// remove and return the item at the front of the queue
// increment the index of front
// update number of elements stored
  string dequeue() {
      if (isEmpty()) {
        return "";
      }

      string result = arr[front];
      arr[front] = "";
      front = (front + 1) % capacity;
      count--;
      return result;
  }  // dequeue

// print the array indexes and contents from index 0 to index MAX_SIZE - 1
// mostly for testing purposes, but might be handy to see the full array when testing
  void printArray() {
      for (int i = 0; i < MAX_SIZE; i++) {
        cout << i << ": " << arr[i] << endl;
      }
  } // printArray

  // like printQueue but it will save the queue to the output stream savefile instead of
  // printing to cout
  void saveQueue(ofstream& savefile) {
  	if (!(savefile.is_open()) ){
  		cout << "No file is open. Returning to main program." << endl;
  		return;
  	}
      for (int i = 0; i < count; i++) {
        savefile << arr[(front + i) % capacity] << endl;
      }
  }

// return the number of elements in the Queue
  int size() {
      return count;
  } // size

// C++ doesn't like reusing the same word ... so can't call the method "front"
// returns the value at the head of the queue but does not change the queue
  string head() {
      if (isEmpty()) {
        return "";
      }
      return arr[front];
  } // head
}; // queue class

int main() {
  Queue q1;
  string value;
  int option;

  // I'm assuming that you would have a standard file name for your task list
  string filename = "tasks.txt";

  do {
    cout << endl;
    cout << "===== Welcome to the Task List Program! Enter 0 to exit ======" << endl;
    cout << "1. Add a task to the list" << endl;
    cout << "2. Finish a task" << endl;
    cout << "3. Check if the task list is empty" << endl;
    cout << "4. Check if the task list is full" << endl;
    cout << "5. Count the number of tasks in the list" << endl;
    cout << "6. Print the full list" << endl;
    cout << "7. Print the next task to complete" << endl;
    cout << "8. Save the task list to tasks.txt" << endl << endl;

    cin >> option;

    switch (option) {
    case 0:
      break;
    case 1:
      cout << "Enter a task to add to the list: " << endl;
        cin.ignore();
      getline(cin, value);
      if (!(q1.enqueue(value))) cout << "Could not add. Task list full." << endl;
      break;
    case 2:
      cout << "Congratulations for completing the task: " << q1.dequeue() << endl;
      break;
    case 3:
      if (q1.isEmpty())
        cout << "The task list is empty" << endl;
      else
        cout << "The task list is NOT empty" << endl;
      break;
    case 4:
      if (q1.isFull())
        cout << "The task list is full" << endl;
      else
        cout << "The task list is NOT full" << endl;
      break;
    case 5:
      cout << "The number of tasks in the list are: " << q1.size() << endl;
      break;
    case 6:
      cout << "Displaying all tasks: " << endl;
      q1.printArray();
      break;
    case 7:
      cout << "Next task in the list: " << endl;
      cout << q1.head() << endl;
	  break;
	case 8: {
	  cout << "Saving task list to " << filename << endl;
	  ofstream savefile(filename);
	  q1.saveQueue(savefile);
	  savefile.close();
	  break;
	}
    default:
      cout << "Please enter a valid option: " << endl;
    }

  } while (option != 0);

  return 0;
}
