// Node class for binary search tree
// has a key field ... normally, we'd have more fields in addition

/*
	Author: Barbara Z. Johnson and <your name here>
	Date: July 2025
	Revised:

*/

#include "btnode.hpp"

// Node class for binary tree
	    
	//constructor for the node
	BTNode::BTNode(int x) {
    	key = x;
        left = nullptr;
        right = nullptr;
    }
    
    // reset the value stored
	void BTNode::setKey(int x) {
		key = x;
	}
	    
	// get the value stored
	int BTNode::getKey() {
		return key;
	}
	    
	// reset left child
	void BTNode::setLeftChild(BTNode * lchild) {
		left = lchild;
	}
	    
	// reset right child
	void BTNode::setRightChild(BTNode * rchild) {
		right = rchild;
	}   
	    
	// get left child
	BTNode * BTNode::getLeftChild() {
		return left;
	}
	    
	    
	// get right child
	BTNode * BTNode::getRightChild() {
		return right;
	}
	    
	    
    	
    	