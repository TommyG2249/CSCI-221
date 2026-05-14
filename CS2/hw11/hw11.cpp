//
// Created by Thomas Glennon on 3/16/26.
//

// Working and efficient supposedly

#include <iostream>
using namespace std;

int bubbleSort(int array[], int length) {

    // Initialize sort analytics
    int comparisons = 0;
    int passes = 0;

    // Main for loop, controls each interation through array
    for (int i = 0; i < length - 1; i++) {

        // If a swap is made in the pass, switches to true and continues passing
        bool swapped = false;

        // Updates passes count every pass
        passes = i + 1;

        // Inner for loop, iterates through array and compares [j] with [j + 1]/
        for (int j = 0; j < length - i - 1; j++) {

            // Updates comparisons for every iteration of inner for loop
            comparisons++;

            // Comparison syntax, swaps items if [j] is greater than [j + 1]
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;

                // Update swap boolean
                swapped = true;
            } // if swap
        } // inner for loop

        // If a pass does not swap any values, stop sorting
        if (!swapped) {
            return 0;
        } // if swapped

        // If i passes through the full index, it will equal length - 1. Stop sorting
        if (i == length - 1) {
            return 1;
        } // if full run
    } // outer for loop

    // Print sort analytics
    cout << "Sort compared array values " << comparisons << " times." << endl;
    cout << "Sort passed the array " << passes << " times." << endl;

} // bubbleSort


// Prints array, inserting newline char every 20 items
void printArray (int array[], int length) {
    int count = 0;
    for (int i = 0; i < length - 1; i++) {
        cout << array[i] << ", ";
        count++;
        if (count >= 20) {
            cout << "\n";
            count = 0;
        } // count if
    } // for loop
    cout << array[length - 1] << endl;
} // func

// Fills array in either forward or backward order with integers up to the length of the array
void fillArray(int array[], int length, bool positive_iter) {
    if (positive_iter == true) {
        for (int i = 0; i < length; i++) {
            array[i] = i;
        } // for
    } // if positive_iter true
    else if (positive_iter == false) {
        for (int i = length - 1; i >= 0; i--) {
            array[(length - 1) - i] = i;
        } // for
    } // elif positive_iter false
} // func

int main() {
    int arrayay[100];
    fillArray(arrayay, 100, false);
    printArray(arrayay, 100);
    bubbleSort(arrayay, 100);
    printArray(arrayay, 100);


    /* This summation below is a representation of the number of comparisons in this bubble sort. It looks like it
     * compares values length - 1 (which is equal to 99 in this case) + length - 2 + length - 3... which totals at 4950
     * times. */
    int sum = 0;
    for (int i = 99; i > 0; i--) {
        sum += i;
    }
    cout << sum << endl;

    return 0;
}