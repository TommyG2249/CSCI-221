// Node class for binary tree

// Node class for binary tree
// all fields and methods are public for convenience
class BTNode {
	private:
		int val;
	    BTNode* left;
	    BTNode* right;
	    
	    
	public:
	    //constructor for the node
	    BTNode(int x);
	    
	    // reset the value stored
	    void setVal(int x);
	    
	    // get the value stored
	    int getVal();
	    
	    // reset left child
	    void setLeftChild(BTNode * lchild);
	    
	    // reset right child
	    void setRightChild(BTNode * rchild);    
	    
	    // get left child
	    BTNode * getLeftChild();
	    
	    
	    // get right child
	    BTNode * getRightChild();
    	
    	
}; // Node class