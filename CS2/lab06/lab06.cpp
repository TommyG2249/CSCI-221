//
// Created by Thomas Glennon on 3/25/26.
//

// This file uses a LinkedList stack implementation I made for hw15
// It will read a string as input from the user and check for 2 conditions
// 1st, it will check if the input contains parentheses
// 2nd, it will check if these parentheses are balanced (each closing parenthesis has a closing parenthesis)

#include <iostream>
#include<limits>
using namespace std;

// Node class to be accessed by LinkedList class
class Node {

    // int data contains a int of user-defined data
    // pt_next is a pointer to the next node in the list
    private:
        char data;
        Node* pt_next;

    // Initializing a node will set the pointer equal to nullptr and the data equal to the parameter data
    public:
        Node(char data1) {
            pt_next = nullptr;
            data = data1;
        }

        // This method returns the data stored in the node
        char getData() {
            return data;
        }

        // This method returns the address of the next item
        Node* getNext() {
            return pt_next;
        }

        // This method (specific to int variable) overwrites the data stored in a node
        void setData(char data2) {
            data = data2;
        }

        // This method assigns a pointer to the next node pointer in a node
        void setNext(Node* next_node) {
            pt_next = next_node;
        }

};

// LinkedList class will directly interface with the Node class, Nodes do not need to be created by the user
class LinkedList {

    // pt_head is a pointer that points to the first node
    // count is the length of the list
    private:
        Node* pt_head;
        int length;

    public:

        // Construction will initialize head to nullptr and count to 0
        LinkedList() {
            pt_head = nullptr;
            length = 0;
        }

        // Destructor iterates through whole list using head and deletes every item
        ~LinkedList() {
            while (pt_head != nullptr) {
                Node* temp_ptr = pt_head;
                pt_head = pt_head->getNext();
                delete temp_ptr;
            }
        }

        bool pushNode(char data) {
            // Print statement
            cerr << "Adding to front: " << data << endl;
            Node* new_node = new Node(data);
            if (pt_head == nullptr) {
                pt_head = new_node;
                new_node->setNext(nullptr);
                length++;
            } else {
                new_node->setNext(pt_head);
                pt_head = new_node;
                length++;
            }
            return true;
        }

        // This method prints the data of the linked list in a list separated by commas
        void printlist() {

            // Initial check if the list is empty
            if (pt_head == nullptr) {
                cout << "List is empty." << endl;
            } else {

                /* Creates temporary iterator pointer to address every item in the
                * list and print that item until the last item */
                Node* current_node_pt = pt_head;
                while (current_node_pt != nullptr) {
                    cout << current_node_pt->getData() << ",";
                    current_node_pt = current_node_pt->getNext();
                }
                cout << endl;
            }
        }

        char getDataAtFront() {
            if (pt_head == nullptr) {
                cout << "List is empty." << endl;
                return -1;
            }
            return pt_head->getData();
        }

        // This method returns the length of the list, stored in the count variable
        int getLength() {
            return length;
        }

            // This method will pop the first node from the list and return that node
        char popNodeFromFront() {

            // Print statement
            cerr << "Removing to front: " << pt_head->getData() << endl;

            /* If the new node is the first item in the list, set the head pointer to the
             * address of the new node, stored in pt_popped_node */
            if (length == 0) {

                cout << "List is empty." << endl;

                return -1;

            }

            Node* ptr_to_delete = pt_head;
            pt_head = pt_head->getNext();
            char result = ptr_to_delete->getData();
            delete ptr_to_delete;

            // Must decrease count
            length--;

            // Return ptr_to_delete
            return result;
        }

};

class Stack {
private:
    int size;
    LinkedList listy;
public:
    Stack() {
        size = 0;
    } // constructor

    bool push(char element) {
        if (listy.pushNode(element)) {
            size++;
            return true;
        }
        return false;
    } // push

    char pop() {
        if (size == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        } // if

        char result = listy.popNodeFromFront();
        size--;
        return result;
    } // pop

    char top() {
        if (size == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return listy.getDataAtFront();
    } // top

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }
};

string inputPrompt(string message) {
    string result;
    cout << message << endl;
    getline(cin, result);
    while (result.empty()) {
        cout << "You entered an empty string! Try again." << endl;
        getline(cin, result);
    }
    return result;
}

string inputToReturn(string message) {
    string result;
    result = inputPrompt(message);
    return result;
}

bool parenthesesCheck(Stack &stack, string input, int &parentheses) {
    int i = 0;
    parentheses = 0;
    bool closed = false;
    for (i = 0; i < input.length(); i++) {
        if (input[i] == '(') {
            stack.push(input[i]);
            parentheses++;
            closed = false;
        }
        if (input[i] == ')') {
            if (stack.isEmpty()) {
                parentheses++;
                return false;
            } else {
                stack.pop();
                closed = true;
            }
        }
    }
    return closed;
}

string outputMessage(bool resultOfPCheck, string input) {
    if (resultOfPCheck) {
        return "Your equation " + input + " uses balanced parentheses!";
    }
    return "Your equation " + input + " contains 1 or more parentheses that were never closed.";
}

string fullPCheckRun(Stack &stack, string input) {
    int parentheses = 0;
    string result = inputToReturn(input);
    bool balanced = parenthesesCheck(stack, result, parentheses);
    if (parentheses == 0) {
        return "The equation you entered contains no parentheses, and is therefore balanced.";
    }
    return outputMessage(balanced, result);
}

int main() {
    Stack stack;
    string message = "Welcome to the Parenthesis Balance Checker!\nEnter a numerical equation, and the program will indicate if all parentheses are balanced.";
    string result = fullPCheckRun(stack, message);
    cout << result << endl;
    return 0;
}