//
// Created by Thomas Glennon on 4/14/26.
//

#ifndef THAPEXSO_NODE_H
#define THAPEXSO_NODE_H

// node.hpp for HW 18 ... holding integers

class Node {
    //defines integer data, and next as a pointer.
private:
    int value; //data each node
    Node *next; //pointer to the next node

public:
    Node(int initdata);

    int getData();

    Node *getNext();

    void setData(int newData);

    void setNext(Node *newnext);

}; // end Node class


#endif
