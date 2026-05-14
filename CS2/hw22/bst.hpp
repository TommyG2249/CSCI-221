// bst tree class header

/*
	Author: Barbara Z. Johnson 
	Date: July 2025
	Revised:

*/

#ifndef _BST_H_
#define _BST_H_

#include "btnode.hpp"

using namespace std;

// the class framework
class BST {
	private:
		BTNode * root;

	public:
		// basic constructor for an empty tree
		BST();
	
		// don't allow duplicates
		// error message & return NULL ... or throw an exception??
		BTNode * insert(int val);
		
		// find the element or return NULL if not found
		BTNode * find(int val, int &count);
		
		// helper method for remove ... 
		// finds the leftmost node in the right subtree of the node to be deleted
		bool delSuccessor(BTNode * current);
		
		bool remove(int val);
		
	   // Print elements in the binary tree as a tree structure
	   void printTree(BTNode* node, int indent);
		
		// starter function called to get the parameterized one going from the root
		void printTree();

};


#endif