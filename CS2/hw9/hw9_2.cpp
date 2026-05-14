//
// Created by Thomas Glennon on 3/9/26.
//

#include <iostream>
#include <string>
using namespace std;

// Node class to be accessed by LinkedList class
class Node {

    // string data contains a string of user-defined data
    // pt_next is a pointer to the next node in the list
    // index will hold an integer value that will order the list
    private:
    // int count is a counter of how many times the item is stored in the list
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
// Cut down from full functionality
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

        Node* gotodata (string data) {
            if (data == "") {
                cerr << "No value entered!" << endl;
                return nullptr;
            }
            Node* current_node_pt = pt_head;
            while (current_node_pt != nullptr && current_node_pt->getData() != data) {
                current_node_pt = current_node_pt->getNext();
            }
            if (current_node_pt == nullptr) {
                cerr << "Data not found!" << endl;
                return nullptr;
            }
            return current_node_pt;
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
            if (length == 0) {
                pt_head = pt_new_node;

                // Iterate count
                length++;

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

                length++;

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

                // Iterate count
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

        bool find(string data) {
            if (gotodata(data) != nullptr) {
                return true;
            }
            return false;
        }

        // This method returns the length of the list, stored in the count variable
        int getLength() {
            return length;
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
            if (length == 0) {
                cout << "List is empty." << endl;
                return 0;
            }

            // If the data is the first item, it can be removed by just accessing the head of the list
            if (pt_head->getData() == remove_data) {
                Node* ptr_to_delete = pt_head;
                pt_head = pt_head->getNext();
                delete ptr_to_delete;

                // Must decrease count
                length--;

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
                length--;

            }

            // Success
            return 1;
        }

        bool putFirst(string data) {
            if (data == "") {
                cerr << "No value entered!" << endl;
                return false;
            }

            if (pt_head == nullptr) {
                cerr << "List is empty." << endl;
                return false;
            }

            Node* current_node_pt = gotodata(data);

            if (current_node_pt == nullptr) {
                cerr << "Data not found!" << endl;
                return false;
            }

            Node* previous_node_pt = pt_head;

            while (previous_node_pt != nullptr && previous_node_pt->getNext() != current_node_pt) {
                previous_node_pt = previous_node_pt->getNext();
            }

            if (previous_node_pt == nullptr) {
                return false;
            }

            previous_node_pt->setNext(current_node_pt->getNext());

            current_node_pt->setNext(pt_head);

            pt_head = current_node_pt;

            return true;

        }
};

int main() {
    LinkedList listy;
    listy.addNodetoFront("zero");
    listy.addNodetoBack("one");
    listy.addNodetoBack("two");
    listy.addNodetoBack("three");
    cout << listy.find("three") << endl;
    cout << listy.find("one") << endl;
    cout << listy.find("pubert") << endl;
    listy.printlist();
    listy.putFirst("three");
    listy.printlist();

}