// Node class for binary tree

#include "btnode.hpp"

// Node class for binary tree
	    
	//constructor for the node
	BTNode::BTNode(int x) {
    	val = x;
        left = nullptr;
        right = nullptr;
    }
    
    // reset the value stored
	void BTNode::setVal(int x) {
		val = x;
	}
	    
	// get the value stored
	int BTNode::getVal() {
		return val;
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
	    
	    
    	
    	