/* 

	Written by faculty of St. Olaf College, Barbara Z Johnson and Tommy Glennon

*/

#include <iostream>
#include <queue>
#include "btnode.hpp"

using namespace std;

// Creating a Binary Tree
class BinaryTree {
	private:
    	BTNode* root;

	public:
    	// Constructor
    	BinaryTree() {
        	root = nullptr;
    	}

    	// Insert elements into the binary tree
    	void insert(int val) {
        	BTNode* newNode = new BTNode(val);
    		BTNode* temp = root;

    		// empty tree
        	if (root == nullptr) {
        		root = newNode;
        		return;
        	}

    		// normal insertion
    		queue<BTNode*> q;
    		q.push(root);

    		while (!q.empty()) {
    			temp = q.front();
    			q.pop();

    			if (temp->getLeftChild() == nullptr) {
    				temp->setLeftChild(newNode);
    				return;
    			}

    			q.push(temp->getLeftChild());

    			if (temp->getRightChild() == nullptr) {
    				temp->setRightChild(newNode);
    				return;
    			}

    			q.push(temp->getRightChild());
    		}
	    } // insert by value
	    
	// traverse from root to parent of last so that we can recycle the child Node's memory
    void deleteLastNode(BTNode * last) {
    	// special case: a single node tree
    	if (last == nullptr) {
    		return;
    	}
    	if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr) {
    		BTNode* temp = root;
    		root = nullptr;
    		delete temp;
    		return;
    	}
    	BTNode* tempParent = root;
    	queue<BTNode*> q;
    	q.push(root);

    	while (!q.empty()) {
    		tempParent = q.front();
    		q.pop();

    		if (tempParent->getRightChild()) {
    			if (tempParent->getRightChild() == last) {
    				tempParent->setRightChild(nullptr);
    				delete last;
    				return;
    			}
    			q.push(tempParent->getRightChild());
    		}

    		if (tempParent->getLeftChild()) {
    			if (tempParent->getLeftChild() == last) {
    				tempParent->setLeftChild(nullptr);
    				delete last;
    				return;
    			}
    			q.push(tempParent->getLeftChild());
    		}

    	}
    	cout << "Node not found!" << endl;
    	// otherwise, find the parent of the last node
    	// hint look at the right-hand child first this time through the traversal
    
    }  

    // Remove an element from the binary tree
    // if the value is not present, return false   
    // while searching for the node with val ALSO locate the last node in the tree
    // then call 
	bool remove(int val) {
		if (root == nullptr) {
			cout << "Cannot remove from empty tree." << endl;
			return false;
		}

		if (root->getLeftChild() == nullptr && root->getRightChild() == nullptr) {
			BTNode* temp = root;
			root = nullptr;
			delete temp;
			return true;
		}

    	BTNode* last = root;
    	BTNode* toBeDeleted = nullptr;
    	queue<BTNode*> q;
    	q.push(root);

    	while (!q.empty()) {
    		last = q.front();
    		q.pop();

    		if (last->getVal() == val) {
    			toBeDeleted = last;
    		}

    		if (last->getLeftChild()) {
    			q.push(last->getLeftChild());
    		}

    		if (last->getRightChild()) {
    			q.push(last->getRightChild());
    		}
    	}

    	if (toBeDeleted != nullptr) {
    		toBeDeleted->setVal(last->getVal());
    		deleteLastNode(last);
    		return true;
    	}
    	cout << "Desired value not found!" << endl;
  		return false;  // silence compiler warning
	}  // remove

	// getter to get root node
	BTNode* getRoot() {
 	   return root;
 	   }

	void printPreOrder() {
    		printPreOrder(root);
    	}

	void printPreOrder(BTNode* node) {
    		if (node == nullptr) {
    			return;
    		}

    		cout << node->getVal() << ", ";

    		printPreOrder(node->getLeftChild());

    		printPreOrder(node->getRightChild());

    	}

	void printInOrder() {
    		printInOrder(root);
    	}

	void printInOrder(BTNode* node) {
    		if (node == nullptr) {
    			return;
    		}

    		printInOrder(node->getLeftChild());

    		cout << node->getVal() << ", ";

    		printInOrder(node->getRightChild());

    	}

	void printPostOrder() {
    		printPostOrder(root);
    	}

	void printPostOrder(BTNode* node) {
    		if (node == nullptr) {
    			return;
    		}

    		printPostOrder(node->getLeftChild());

    		printPostOrder(node->getRightChild());

    		cout << node->getVal() << ", ";

    	}

	// Print elements in the binary tree as a tree structure
	void printTree(BTNode* node, int indent = 0) {
    	if (node == nullptr) {
            return;
    	}
    	printTree(node->getRightChild(), indent + 4);
    	for (int i = 0; i < indent; i++) {
            cout << " ";
    	}
    	cout << node->getVal() << endl;
    	printTree(node->getLeftChild(), indent + 4);
    }

    void printTree() {
        printTree(root);
}}; // Binary Tree class

int main() {
   BinaryTree tree;
    
    tree.insert(4); 
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    cout << "Binary Tree:" << endl;
    tree.printTree();
	cout << "Binary Tree values in pre-order:" << endl;
	tree.printPreOrder();
	cout << endl;
	cout << "\nBinary Tree values in order:" << endl;
	tree.printInOrder();
	cout << endl;
	cout << "\nBinary Tree values in post-order:" << endl;
	tree.printPostOrder();
	cout << endl;


    
    /*
	tree.remove(4);
	tree.remove(2);
	cout << "Binary Tree:" << endl;
	tree.printTree();

	tree.remove(100);
	cout << "Binary Tree:" << endl;
	tree.printTree();

	BinaryTree tree2;

	if (!tree2.remove(1)) {
		cout << "Cannot remove value that does not exist." << endl;
	} */

    return 0;
}

