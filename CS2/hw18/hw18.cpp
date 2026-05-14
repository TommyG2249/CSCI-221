//
// Created by Thomas Glennon on 4/20/26.
//

/*

	starter code for trying out different hash functions

	Author: Barbara Z Johnson
	Date: February 11, 2025
	Revised: February 12, 2025

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define SIZE 31          // hash table sizes are often prime numbers to attempt to avoid collisions

using namespace std;

// define a struct to use in creating variables and hashing
struct Student {
	string informal_name;
	string surname;
	int ID_num;
	string email;
};


// YOUR HASH FUNCTION HERE
// it is OK to send in the student variable and not a pointer to it because we are not changing
// the values and the structure is small
// CALCULATE A NUMBER between 0 and SIZE - 1 that the program can use to find the slot
// where the student record should be.
int calc_hash_alt(Student stu) {
	int value = 0;
	long long intermed = (long long)stu.ID_num * stu.ID_num;
    intermed = intermed % 1000;
    value = intermed % SIZE;
	return value;
}

int calc_hash(Student stu) {
	int value = 0;
	int surname_num = 0;
    int inf_name_num = 0;
    
    for (int i = 0; i < stu.surname.length(); i++) {
        surname_num += stu.surname[i] * (i + 1);
    }

    for (int i = 0; i < stu.informal_name.length(); i++) {
        inf_name_num += stu.informal_name[i] * (i + 1);
    }

    if (inf_name_num >= surname_num) {
		surname_num += stu.ID_num;
		surname_num += inf_name_num;
        value = surname_num % SIZE;
    } else {
		inf_name_num += stu.ID_num;
		inf_name_num += surname_num;
        value = inf_name_num % SIZE;
    }

	return value;
}

int main(int argc, char * argv[]) {

	int count = 0;   // the number of student records read and processed
	ifstream infile;

	// get name of file off of command line and recover from errors of missing file name or
	// missing or unopenable file
	if (argc < 2) {
		cerr << "Missing file name.  Usage: ./hash_function_trials <inputfile>" << endl;
		exit(1);   // minor error
	}

	infile.open(argv[1]);
	if (!infile.is_open()) {
		cerr << "Could not open " << argv[1] << endl;
		exit(1);
	}

	// create a table that will track the number of times an object would have been placed in that location
	int num_placements[SIZE] = {0};
	int num_placements_alt[SIZE] = {0};

	// if we get here, the file has been found and successfully opened
	// read data from the file in a while loop ... read each line and parse the line into pieces
	string line;
	while (getline(infile, line)) {   // while there are lines to read from the file
//		cout << line << endl;           // confirming the input

		vector<string> stu_string;      // will hold parts of the student record as strings
		stringstream ss(line);          // create the string stream from the input string
		string piece;					// each piece of the student record as a string

		while (getline(ss, piece, ',')) {		//  break the line into substrings & save in vector
			stu_string.push_back(piece);
		}

		// probably should do error checking if there were not 4 pieces on that line
		if (stu_string.size() < 4) {
			cerr << "Bad input line.  Skipping" << endl;
			continue;
		}

/*

		cout << "Component pieces" << endl;  // testing
		for (int i = 0; i < 4; i++) {
			cout << stu_string[i] << endl;

		}

*/

		// create a variable from the input line
		 Student stu;
		 stu.informal_name = stu_string[0];
		 stu.surname = stu_string[1];
		 stu.ID_num = stoi(stu_string[2]);
		 stu.email = stu_string[3];


		// hash based on one or more fields of the class
		// CALL YOUR FUNCTION HERE
		int result = calc_hash(stu);
		int result_alt = calc_hash_alt(stu);

		num_placements[result]++;
		num_placements_alt[result_alt]++;
		// increment the value in the table for each time the hash would result in placement there
		count++;

    }  // while reading lines from the file

    cout << "Number of lines processed: " << count << endl;

	// if the file was opened, close it
	if (infile.is_open()) {
		infile.close();
	}



	// report
	cout << "The count for each hash index: " << endl;
	for (int i = 0; i < SIZE; i++) {
		printf("Index %2d, number of insertions: %d\n", i, num_placements[i]);
	}

	cout << endl;

	cout << "The count for each hash index using the alternate hash function: " << endl;
	for (int i = 0; i < SIZE; i++) {
		printf("Index %2d, number of insertions: %d\n", i, num_placements_alt[i]);
	}



	return 0;
}