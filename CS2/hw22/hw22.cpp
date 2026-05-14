// the main program for the BST homework program that will demonstrate the order of
// complexity for the find() method.

/*
	Author: Barbara Z. Johnson and Tommy Glennon
	Date: July 2025
	Revised:

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "bst.hpp"

#define MAX_VAL 300

string BST_Test(BST tree, int &count, int size, int array[]) {
	count = 0;
	int sum = 0;
	string result = "t" + to_string(size) + ",";
	for (int i = 0; i < 5; i++) {
		count = 0;
		if (tree.find(array[i], count) == nullptr) {
			result += to_string(count) + ",";
			sum += count;
		} else {
			result += "f" + to_string(count) + ",";
			sum += count;
		}
	}
	result += to_string(static_cast<float>(sum) / 5.0);
	return result + "\n";
}

int main() {

	srand(time(0));

	BST t15;
	BST t31;
	BST t63;
	BST t127;
	BST t255;

	int rando = 0;
	for (int i = 0; i < 15; i++) {
		rando = rand() % 300;
		t15.insert(rando);
		t31.insert(rando);
		t63.insert(rando);
		t127.insert(rando);
		t255.insert(rando);
	}

	for (int j = 0; j < 16; j++) {
		rando = rand() % 300;
		t31.insert(rando);
		t63.insert(rando);
		t127.insert(rando);
		t255.insert(rando);
	}

	for (int k = 0; k < 32; k++) {
		rando = rand() % 300;
		t63.insert(rando);
		t127.insert(rando);
		t255.insert(rando);
	}

	for (int L = 0; L < 64; L++) {
		rando = rand() % 300;
		t127.insert(rando);
		t255.insert(rando);
	}

	for (int m = 0; m < 128; m++) {
		rando = rand() % 300;
		t255.insert(rando);
	}

	int remove_nodes[5];

	for (int n = 0; n < 5; n++) {
		rando = rand() % 300;
		remove_nodes[n] = rando;
		t15.remove(remove_nodes[n]);
		t31.remove(remove_nodes[n]);
		t63.remove(remove_nodes[n]);
		t127.remove(remove_nodes[n]);
		t255.remove(remove_nodes[n]);
	}

	fstream fout;

	fout.open("BST_Find_Tommy_Glennon.csv", ios::out | ios::app);

	int count = 0;

	fout << "Tree Name, Find " << remove_nodes[0] << ", Find " << remove_nodes[1] << ", Find "
	<< remove_nodes[2] << ", Find " << remove_nodes[3] << ", Find " << remove_nodes[4] << ", Average\n";

	fout << BST_Test(t15, count, 15, remove_nodes);
	fout << BST_Test(t31, count, 31, remove_nodes);
	fout << BST_Test(t63, count, 63, remove_nodes);
	fout << BST_Test(t127, count, 127, remove_nodes);
	fout << BST_Test(t255, count, 255, remove_nodes);

	fout.close();

	return 0; 
}