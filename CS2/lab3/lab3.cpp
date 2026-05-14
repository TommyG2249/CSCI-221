//
// Created by Thomas Glennon on 3/4/26.
//
// cin.ignore(INT_MAX) was a suggestion made on https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer because as I understand the cin buffer will still contain a newline character after cin >> option and getline() will read the newline character
#include <iostream>
#include <string>
using namespace std;

// Node class to be accessed by LinkedList class
class Node {

    // string data contains a string of user-defined data
    // pt_next is a pointer to the next node in the list
    private:
        string data;
        Node* pt_next;

    // Initializing a node will set the pointer equal to nullptr and the data equal to the parameter data
    public:
        Node(string data1) {
            pt_next = nullptr;
            data = data1;
        }

        // This method returns the data stored in the node
        string getData() {
            return data;
        }

        // This method returns the address of the next item
        Node* getNext() {
            return pt_next;
        }

        // This method (specific to string variable) overwrites the data stored in a node
        void setData(string data2) {
            if (data2 != "") {
                data = data2;
            } else {
                cout << "No value entered. Previous value retained." << endl;
            }
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
        int count;

    public:

        // Construction will initialize head to nullptr and count to 0
        LinkedList() {
            pt_head = nullptr;
            count = 0;
        }

        // Destructor iterates through whole list using head and deletes every item
        ~LinkedList() {
            while (pt_head != nullptr) {
                Node* temp_ptr = pt_head;
                pt_head = pt_head->getNext();
                delete temp_ptr;
            }
        }


        // This method will add a new node containing parameter data to the back of the list
        bool addNodetoBack(string data) {

            // Empty data catch
            if (data == "") {
                cerr << "No value entered!" << endl;
                return false;
            }

            // Print statement
            cerr << "Adding to back: " << data << endl;

            // Create new anonymous node containing data from parameter, address stored in pt_new_node
            Node* pt_new_node = new Node(data);

            // If node creation fails, return false to later define an error
            if (pt_new_node == nullptr) {
                cout << "Node creation failed!" << endl;
                return false;
            }

            /* If the new node is the first item in the list, set the head pointer
             * to the address of the new node, stored in pt_new_node */
            if (count == 0) {
                pt_head = pt_new_node;

                // Iterate count
                count++;

            } else {

                /* Creates a temporary pointer to store the current address as the list is read
                 * from the front down. The linked list only knows where the first element is stored,
                 * so this block, which reads down the list until a defined end, must access all nodes
                 * to compare to the end definition (in this case, it's looking for the node which points to nullptr) */
                Node* current_node_pt = pt_head;

                /* Looks at the current node, it's next address, and, if it's not null,
                * moves the current node to the following */
                while (current_node_pt->getNext() != nullptr) {
                    current_node_pt = current_node_pt->getNext();
                }

                /* The new node is already made and points to nullptr,
                * so all we do is set the current final node to point to our new final node */
                current_node_pt->setNext(pt_new_node);
                count++;
            }

            // Return true so no error is thrown
            return true;
        }

        // This method will add a new node with parameter data to the front of the list
        bool addNodetoFront(string data) {

            // Empty data catch
            if (data == "") {
                cerr << "No value entered!" << endl;
                return false;
            }

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
            if (count == 0) {

                pt_head = pt_new_node;

                // Iterate count
                count++;
            } else {

                /* If it's not the first item, set the next pointer of the new node
                 * to the current head (points to current first item) */
                pt_new_node->setNext(pt_head);

                // Then, set the head pointer to the address of the new node, stored in pt_new_node
                pt_head = pt_new_node;

                // Iterate count
                count++;
            }

            // Return true so no error is thrown
            return true;
        }

        bool addNodetoIndex(string data, int index) {

            // Empty data catch
            if (data == "") {
                cerr << "No value entered!" << endl;
                return false;
            }

            // Print statement
            cerr << "Adding to index " << index << ": " << data << endl;

            // Bounds checking

            // If the parameter index == 0, just calls addtofront
            if (index == 0) {
                return addNodetoFront(data);
            }

            // Checks if the desired index is longer than the count of the list.
            if (index > count || index < 0) {
                cout << "This index is out of range. The list contains " << count << " items" << endl;
                return false;
            }


            // Create new anonymous node containing data from parameter, address stored in pt_new_node
            Node* pt_new_node = new Node(data);

            // If node creation fails, return false to later define an error
            if (pt_new_node == nullptr) {
                cout << "Node creation failed!" << endl;
                return false;
            }

            /* If the new node is the first item in the list, set the head pointer to the
             * address of the new node, stored in pt_new_node */
            if (count == 0) {
                pt_head = pt_new_node;

                // Iterate count
                count++;
            } else {

                /* Creates a temporary pointer to store the current address as the list is read
                 * from the front down. The linked list only knows where the first element is stored,
                 * so this block, which reads down the list until a defined end, must access all nodes
                 * to compare to the end definition (in this case, it's looking for the node which points to nullptr)
                 * Another node address (previous_node_ptr) is necessary because 2 addresses must be written to insert
                 * between two nodes. the current_node_ptr will be assigned to the new_node, and the previous_node_pt
                 * will change its next address to the new_node_ptr.
                 */
                Node* current_node_pt = pt_head;
                Node* previous_node_pt = nullptr;

                /* Creates a counter variable (index_number) to count the index of each item
                * in the list and insert the node at the right point. */
                int index_number = 0;

                /* Looks at the current node and previous node, it's next address, and, if it's not null,
                * moves the current node to the following
                * Another index check occurs to make sure index is not out of range with != nullptr. */
                while (current_node_pt != nullptr && index_number != index) {
                    previous_node_pt = current_node_pt;
                    current_node_pt = current_node_pt->getNext();
                    index_number++;
                }

                /* The new node is already made and points to nullptr,
                * so all we do is set the previous  node to point to our new  node and the new node to point to
                * the current node.
                 */
                previous_node_pt->setNext(pt_new_node);
                pt_new_node->setNext(current_node_pt);
                count++;
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

        // This method returns the length of the list, stored in the count variable
        int length() {
            return count;
        }

        // This method takes data as input string and finds the node containing that data. The node is removed
        // 0 is a code for empty list
        // 1 is a code for success
        // 2 is a code for remove_data not found
        int removeData(string remove_data) {

            // Empty data catch
            // Return value 3 indicates no data error
            if (remove_data == "") {
                cerr << "No value entered!" << endl;
                return 3;
            }

            // Print statement
            cerr << "Removing data: " << remove_data << endl;

            // Checks if the list is empty, in which case it will throw an error defined by false bool return
            if (pt_head == nullptr) {
                cout << "List is empty." << endl;
                return 0;
            }

            // Double-check for empty list
            if (count == 0) {
                cout << "List is empty." << endl;
                return 0;
            }

            // If the data is the first item, it can be removed by just accessing the head of the list
            if (pt_head->getData() == remove_data) {
                Node* ptr_to_delete = pt_head;
                pt_head = pt_head->getNext();
                delete ptr_to_delete;

                // Must decrease count
                count--;
            } else {
                /* Creates 2 temporary nodes to track the current node and previous node. When the current node's data
                 * == to remove_data, it stops, stores the node to be deleted in a temp pointer, and assigns the
                 * previous node's next_ptr to the next_ptr stored in the node to be deleted. Then the temp ptr is
                 * deleted */
                Node* current_node_pt = pt_head;
                Node* previous_node_pt = nullptr;

                // While loop that loops until current_node_ptr reaches the node with desired data to delete
                while (current_node_pt->getData() != remove_data) {
                    previous_node_pt = current_node_pt;
                    current_node_pt = current_node_pt->getNext();

                    // Error check to see if current_node_ptr doesn't find the remove_data
                    if (current_node_pt == nullptr) {
                        cout << "The data you entered is not in the list." << endl;
                        return 2;
                    }
                }

                // Sets the previous node's next_ptr to the node after the current node to be deleted
                previous_node_pt->setNext(current_node_pt->getNext());
                delete current_node_pt;

                // Always decrease the count
                count--;

            }

            // Success
            return 1;
        }


};

void printMenu () {
    cout << "Select your choice by entering the corresponding number" << endl << endl << "1. Add a task" << endl << "2. Remove a task" << endl << "3. Show all tasks" << endl << "4. Quit" << endl;
}

void printChoice (int option, LinkedList &task_list, bool &cont) {

    switch (option) {
        case 1: {
            cout << "Adding a task" << endl << endl;
            string task_to_add;
            cout << "Enter the task to be added." << endl;
            cin.ignore();
            getline(cin, task_to_add);
            task_list.addNodetoBack(task_to_add);
            break;
        }

        case 2: {
            cout << "Removing a task" << endl << endl;
            string task_to_remove;
            cout << "Enter the task to be removed." << endl;
            cin.ignore();
            getline(cin, task_to_remove);
            task_list.removeData(task_to_remove);
            break;
        }

        case 3: {
            cout << "Showing all tasks" << endl << endl;
            task_list.printlist();
            break;
        }
        case 4: {
            cout << "Quitting" << endl << endl;
            cont = false;
            break;
        }
    }
}




int main () {

    int option;
    bool cont = true;
    LinkedList task_list;

    cout << "Welcome to the task manager!" << endl;
    while (cont == true) {
        printMenu();


        while (!(cin >> option) || option < 1 || option > 4) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input! Please only enter one number 1-4." << endl;
            printMenu();
        }

        printChoice(option, task_list, cont);
    }

    return 0;
}