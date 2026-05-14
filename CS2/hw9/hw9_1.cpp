//
// Created by Thomas Glennon on 3/9/26.
//

#include <iostream>
#include <string>
using namespace std;

int find (string names[], string item, int arraylength) {
    for (int i = 0; i < arraylength; i++) {
        if (names[i] == item) {
            return i;
        } // if
    } // for
    return -1;
} // find

int main () {
    string arraynames[] = { "A", "B", "C", "D", "E", "F" };
    cout << find(arraynames, "A", 6) << endl;
    cout << find(arraynames, "B", 6) << endl;
    cout << find(arraynames, "pubert", 6) << endl;
}