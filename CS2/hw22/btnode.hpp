// Node class for binary search tree

/*
	Author: Barbara Z. Johnson
	Date: July 2025
	Revised:

*/

#ifndef _BTNODE_H_
#define _BTNODE_H_

class BTNode {
	private:
		int key;
	    BTNode* left;
	    BTNode* right;
	    
	    
	public:
	    //constructor for the node
	    BTNode(int x);
	    
	    // reset the value stored
	    void setKey(int x);
	    
	    // get the value stored
	    int getKey();
	    
	    // reset left child
	    void setLeftChild(BTNode * lchild);
	    
	    // reset right child
	    void setRightChild(BTNode * rchild);    
	    
	    // get left child
	    BTNode * getLeftChild();
	    
	    // get right child
	    BTNode * getRightChild();
    	
    	
}; // Node class

#endif