#include <cstddef>
#include "node.hpp"


        Node::Node(int initdata) {
            value = initdata; //the initialized data is set as the head
            next = nullptr; //the next node is set as NULL, as there is no next node yet.
        }

int Node::getData() { //function that return data of a given node.
            return value;
        }

Node * Node::getNext() { // pointer that gets the next node
            return next;
        }

void Node::setData(int newData) { // sets data in node
            value = newData;
        }

void Node::setNext(Node *newnext) {
            next = newnext;
        }