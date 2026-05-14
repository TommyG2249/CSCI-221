//
// Created by Thomas Glennon on 3/25/26.
//

// This is the same program as hw14 but just with a linked list instead of an array. I'm using my own linked list class

#include <iostream>
#include<limits>
using namespace std;

// Node class to be accessed by LinkedList class
class Node {

    // int data contains a int of user-defined data
    // pt_next is a pointer to the next node in the list
    private:
        int data;
        Node* pt_next;

    // Initializing a node will set the pointer equal to nullptr and the data equal to the parameter data
    public:
        Node(int data1) {
            pt_next = nullptr;
            data = data1;
        }

        // This method returns the data stored in the node
        int getData() {
            return data;
        }

        // This method returns the address of the next item
        Node* getNext() {
            return pt_next;
        }

        // This method (specific to int variable) overwrites the data stored in a node
        void setData(int data2) {
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

        void pushNode(int data) {
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
        }

        // This method will add a new node with parameter data to the front of the list
        bool addNodetoFront(int data) {

            // Print statement
            cerr << "Adding to front: " << data << endl;

            // Create new anonymous node containing data from parameter, address stored in pt_new_node
            Node* pt_new_node = new Node(data);

            // If node creation fails, return false to later define an error
            if (pt_new_node == nullptr) {
                cout << "Node creation failed!" << endl;
                return false;
            }

            /* If the new node is the first item in the list, set the head pointer to the
             * address of the new node, stored in pt_new_node */
            if (length == 0) {

                pt_head = pt_new_node;

                // Iterate count
                length++;

            } else {

                Node* current_node_pt = pt_head;

                /* Looks at the current node, it's next address, and, if it's not null,
                * moves the current node to the following and increases index
                * While doing the above, this bloc also increases the index of every node in the
                * list by one in preparation for the new head of the list, which has an index initialized to 0 */
                while (current_node_pt->getNext() != nullptr) {
                    current_node_pt = current_node_pt->getNext();
                }


                /* If it's not the first item, set the next pointer of the new node
                 * to the current head (points to current first item) */
                pt_new_node->setNext(pt_head);

                // Then, set the head pointer to the address of the new node, stored in pt_new_node
                pt_head = pt_new_node;

                // Iterate size
                length++;

            }

            // Return true so no error is thrown
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

        int getDataAtFront() {
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
        int popNodeFromFront() {

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
            int result = ptr_to_delete->getData();
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

    void push(int element) {
        listy.pushNode(element);
        size++;
    } // push

    int pop() {
        if (size == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        } // if

        int result = listy.popNodeFromFront();
        size--;
        return result;
    } // pop

    int top() {
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

string decimalToBinary(unsigned short number) {
    Stack stack;
    short base = 2;
    while (number > 0) {
        int remainder = number % base;
        stack.push(remainder);
        number = number / base;
    }
    string result;
    while (!stack.isEmpty()) {
        result += to_string(stack.pop());
    }

    while (result.length() < 16) {
        result = "0" + result;
    }

    result.insert(12, " ");
    result.insert(8, " ");
    result.insert(4, " ");

    return result;
}

bool inputCheck (unsigned short input) {
    bool result = false;
    if (input >= 0 && input <= 65535) {
            result = true;
        }
    return result;
}

unsigned short inputWrapper(string message) {
    unsigned short input = 0;
    cout << message << endl;
    bool pass = false;
    while (pass == false) {
        if (!(cin >> input)) {
            cout << "Invalid input" << endl;
            cin.clear();
            // got this line from https://www.geeksforgeeks.org/cpp/how-to-validate-user-input-in-cpp/
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message << endl;
        } else if (!(inputCheck(input))) {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message << endl;
        } else {
            pass = true;
        } // else
    } // while
    return input;
}

int main () {
    unsigned short input;
    input = inputWrapper("Please enter a number between 0 and 65535");
    cout << decimalToBinary(input) << endl;
}