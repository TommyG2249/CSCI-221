// testing program for the BST class and Node structure

/*
	Author: Barbara Z. Johnson and <your name here>
	Date: July 2025
	Revised:

*/

#include <iostream>
#include "btnode.hpp"
#include "bst.hpp"


int main() {
	
	// create a BST tree
	BST test_tree;
	
	// print the empty tree
	test_tree.printTree();

	int count2 = 0;

	// add nodes and print the tree to confirm that they were added
	test_tree.insert(20);
	test_tree.insert(15);
	test_tree.insert(10);
	test_tree.insert(5);
	// test that it will NOT allow a duplicate (try a duplicate and print the tree again)
	test_tree.insert(5);
	// add more nodes
	test_tree.insert(384);
	test_tree.printTree();
	// add a node and print ... did it add correctly??
	test_tree.insert(67);
	test_tree.printTree();

	cout << "Find will return the value it finds in the tree. It is tasked with finding 384: " << endl;
	cout << "Found " << test_tree.find(384, count2)->getKey() << " in " << count2 << " steps." << endl;

	cout << "This find should return a null pointer. If it does, the console will print nullptr." << endl;
	if (test_tree.find(82430, count2) == nullptr) {
		cout << "nullptr" << endl;
	} else {
		cout << "Something went wrong!" << endl;
	}

	// remove node with one child and print the tree
	test_tree.remove(384);
	test_tree.printTree();
	// try to remove a node that didn't get added
	test_tree.remove(82430);
	test_tree.printTree();
	// remove the root and print the tree
	test_tree.remove(20);
	test_tree.printTree();
	// remove a leaf & print the tree
	test_tree.remove(5);
	test_tree.printTree();

	// find nodes that are in the tree to be sure that find() works
	cout << "Testing finding specific nodes\n";
	test_tree.insert(22);   // make sure it's there to find
	int count = 0;
	BTNode * loc = test_tree.find(22, count);
	if (loc) {
		cout << "Found " << loc->getKey() << endl;  
		cout << "It counted " << count << " steps." << endl;
	}
	
	// try to find some that don't exist in the tree and count the number of nodes visited
	count = 0;
	test_tree.remove(20);
	loc = test_tree.find(20, count);
	if (loc) {
		cout << "Found " << loc->getKey() << endl;  
	} else {
		cout << "Didn't find 20" << endl;
	}
	cout << "It counted " << count << " steps." << endl;
	
	count = 0;
	test_tree.remove(15);
	loc = test_tree.find(15, count);
	if (loc) {
		cout << "Found " << loc->getKey() << endl;  
	} else {
		cout << "Didn't find 15" << endl;
	}
	cout << "It counted " << count << " steps." << endl;
	


	return 0;
}