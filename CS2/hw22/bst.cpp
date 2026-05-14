// bst tree class implementation for HW21
// starter code contains the remove method and printTree method plus helper methods
// you need to create the insert and find methods

/*
	Author: Barbara Z. Johnson and Tommy Glennon
	Date: July 2025
	Revised:

*/

#include <iostream>
#include "btnode.hpp"
#include "bst.hpp" 

using namespace std;

	BST::BST() {
		root = nullptr;
	}

	// insert returns the pointer to the node that contains the key
	// will not add a duplicate key
	BTNode * BST::insert(int val) {
		// YOUR CODE GOES HERE!
		
		// empty tree
		if (root == nullptr) {
			root = new BTNode(val);
			return root;
		}

		BTNode * prev = nullptr;
		BTNode * curr = root;
		BTNode * successor = new BTNode(val);

		while (curr != nullptr) {

			if (curr->getKey() == val) {
				cout << curr->getKey() << " is already in the tree." << endl;
				delete successor;
				return nullptr;
			} // duplicate case handling

			if (val < curr->getKey()) {
				prev = curr;
				curr = curr->getLeftChild();
			} else if (val > curr->getKey()) {
				prev = curr;
				curr = curr->getRightChild();
			}

			}
		if (val < prev->getKey()) {
			prev->setLeftChild(successor);
		} else if (val > prev->getKey()) {
			prev->setRightChild(successor);
		}
		
		// create new BTNode (can be done after finding where the new node should be added)

			
	   // look for where the node goes (no duplicates allowed)
	   
	   
	   // Add the node
		
	   // return the pointer to the new Node 
		return successor;   // silencing compiler warning in starter code ... remove once you have added your code
	} // end of insert
	


	BTNode * BST::find(int val, int &count) {
		count = 0;
		// empty tree
		if (root == nullptr) {
			return nullptr;
		}

		BTNode * curr = root;

		while (curr != nullptr && curr->getKey() != val) {
			if (val < curr->getKey()) {
				curr = curr->getLeftChild();
			} else if (val > curr->getKey()) {
				curr = curr->getRightChild();
			}
			count++;
		}
		if (curr == nullptr) {
			// if we get here, the item is not in the tree
			cout << val << " not found\n" << endl;
		}
		return curr;
		
	} // end of find
		
	// helper for remove
	// finds the leftmost node in the right subtree of the node to be deleted
	bool BST::delSuccessor(BTNode * current) {
		//	cout << "In delSuccessor\n";
		//	cout << "Current's value: " << current->val << endl;
		BTNode * parent = current;
		BTNode * successor = current->getRightChild();
			
		while (successor != nullptr && successor->getLeftChild() != nullptr) {
			parent = successor;
			successor = successor->getLeftChild();
		}
			
		int temp = successor->getKey();
		current->setKey(temp);
			
		if (parent == current) {  // delete right child
			parent->setRightChild(nullptr); 
			delete successor;
			return true;
		} else {  // delete the left child
			parent->setLeftChild(nullptr);
			delete successor;
			return true;
		}

		return false;
	} // end of delSuccessor
		
	// remove if found and return true
	// otherwise, leave tree unchanged and return false
	bool BST::remove(int val) {
		// empty tree
		if (root == nullptr) {
			return false;
		}
		
		BTNode * prev = nullptr;
		BTNode * curr = root;
		
		while (curr != nullptr) {
			// cout << "At: " << curr->val << endl;
            if (curr->getKey() == val) {
    			//	cout << "At location\n";
                // case 1: no children
                    if (curr->getLeftChild() == nullptr && curr->getRightChild() == nullptr) {
                    //	cout << "No children\n";
                        if (curr == root) { // root is a special case
                            root = nullptr;
                            delete curr;
                            return true;
                        }
                        else if (val < prev->getKey()) {
                            prev->setLeftChild(nullptr);
                        } else {
                            prev->setRightChild(nullptr);
                        }
                        delete curr;
                        return true;
                    } // no children
                    
                   
                    // case 3: two children
            		//  cout << "Two children of " << curr->val << endl;
                    if (curr->getRightChild() != nullptr && curr->getLeftChild() != nullptr) {
                    	bool succ = delSuccessor(curr);
                    	
                    	if (succ) {
                    		return true;
                    	} else {
                    		return false;
                    	}
                    	
                    }  // two children
                   
                    // case 2: one child only
                //    cout << "One child\n";
                    if (curr->getLeftChild() != nullptr) {
                    //	cout << "Left child of current\n";
                    	if (curr == root) {  // root is a special case
                    		root = curr->getLeftChild();
                    		delete curr;
                    		return true;
                    	} else if (val < prev->getKey()) {
                    		prev->setLeftChild(curr->getLeftChild());
                    	} else {
                    		prev->setRightChild(curr->getLeftChild()); 
                    	}
                    	delete curr;
                    	return true;
                    }  // pulling up left child
                    else if (curr->getRightChild() != nullptr) {
                    	//cout << "Right child of current exists\n";
                    	if (curr == root) {   // root is a special case
                    	//	cout << "Root\n";
                    		root = curr->getRightChild();
                    		delete curr;
                    		return true;
                    	} else if (val < prev->getKey()) {
                    	//	cout << "Prev val: " << prev->val << endl;
                    		prev->setLeftChild(curr->getRightChild());
                    	} else {
                    		prev->setRightChild(curr->getRightChild());
                    	}
                    	delete curr;
                    	return true; 
                    }  // pulling up right child
                
                    return true;
                }  // found the node to delete
                
                // keep searching  ... PREVIOUS needs to move too, remember!
                if (val < curr->getKey()){ // go left
                	prev = curr;
                    curr = curr->getLeftChild();
                } else { // go right
                	prev = curr;
                    curr = curr->getRightChild();
                }

			} // while traversing the tree to delete
			return false;  // the value was not found
		}  // end of remove method
		

	// Print elements in the binary tree as a tree structure
	// increasing indent with each recursive call to the subtree
	// Not a DPS in-order because we are printing the right-most as the top line
	 void BST::printTree(BTNode* node, int indent = 0) {
	 	if (node == nullptr) {
	 		return;
	 	}
	 	
	 	// handle right/top line
	 	printTree(node->getRightChild(), indent + 4);
	 	
	 	// print indent with spaces
	 	for (int i = 0; i < indent; i++) {
	 		cout << " " ;
	 	}
	 	cout << node->getKey() << endl;
	 	
	 	// handle left subtree
	 	printTree(node->getLeftChild(), indent + 4);
	   
	   
	}
		
	// helper to start the recursive printTree
	void BST::printTree() {
	   	if (root == nullptr) {
	   		cout << "Tree is empty" << endl;
	   		return;  
	   	}
	   	
	   	cout << "=====================================================" << endl;
		printTree(root);
	}



