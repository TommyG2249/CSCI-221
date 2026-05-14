//
// Created by Thomas Glennon on 3/18/26.
//

#include <iostream>
#include <vector>
#define INTY 100
using namespace std;

// insertion sort

void insertionSort(vector<int> &arr) {
    // analytic tallies
    int comparisons = 0;
    int assign = 0;

    // init target and comp_pos
    int target;
    int comp_pos;

    // loops through entire vector
    for (int i = 0; i < arr.size(); i++) {

        // the target of the sort is arr[i], will begin by comparing that and -1
        target = arr[i];
        comp_pos = i;

        /* while loop continues until the comp_pos reaches the beginning of the vector
         * OR until the comp_pos-1 is less that the target of the sort */
        while (++comparisons && comp_pos > 0 && arr[comp_pos-1] > target) {

            /* So when the number below the comp_pos (target in base case) is greater than comp_pos, we put the bigger
             * number in comp_pos. Increment assign and move the comp_pos down (which should be the same number) so the
             * next loop can compare with the number before that.
             */
            arr[comp_pos] = arr[comp_pos-1];
            assign++;
            comp_pos--;
        } // inner while

        // Whatever is at the comp_pos has it's value copied at comp_pos +1, so we put the target at comp_pos
        arr[comp_pos] = target;
    } // outer for
    printf("Comparsions: %d\n", comparisons);
    printf("Assignments: %d\n", assign);
} // insertionSort

// Prints vector, inserting newline char every 20 items, took this from my hw11
void printVector (vector <int> vecy) {
    int count = 0;
    for (int i = 0; i < vecy.size() - 1; i++) {
        cout << vecy[i] << ", ";
        count++;
        if (count >= 20) {
            cout << "\n";
            count = 0;
        } // count if
    } // for loop
    cout << vecy[vecy.size() - 1] << endl;
} // func

// Fills vector in either forward or backward order with integers up to the length of the array, from my hw11
void fillVector(vector <int> &vecta, bool positive_iter) {
    if (positive_iter == true) {
        for (int i = 0; i < vecta.size(); i++) {
            vecta[i] = i;
        } // for
    } // if positive_iter true
    else if (positive_iter == false) {
        for (int i = vecta.size() - 1; i >= 0; i--) {
            vecta[(vecta.size() - 1) - i] = i;
        } // for
    } // elif positive_iter false
} // func

// bubble sort

int bubbleSort(int array[], int length) {

    // Initialize sort analytics
    int comparisons = 0;
    int passes = 0;
    int assignments = 0;

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
                assignments++;
                array[j] = array[j + 1];
                assignments++;
                array[j + 1] = temp;
                assignments++;

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
    printf("Sort swapped values %d times.\n", assignments);

}

// bubbleSort

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

    cout << "Vector insertion sort:" << endl;
    vector<int> vecy(INTY);
    fillVector(vecy, false);
    printVector(vecy);
    insertionSort(vecy);
    printVector(vecy);
    cout << endl;

    cout << "Array bubble sort:" << endl;
    int arrayay[INTY];
    fillArray(arrayay, INTY, false);
    printArray(arrayay, INTY);
    bubbleSort(arrayay, INTY);
    printArray(arrayay, INTY);
    cout << endl;

    return 0;
}