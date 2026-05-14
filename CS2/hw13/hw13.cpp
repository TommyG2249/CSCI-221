//
// Created by Thomas Glennon on 3/20/26.
//

#include <iostream>
#include <vector>
#include <cmath>

#define INTY 100
using namespace std;

// Alright so. We need to recursively divide the array into smalled subarrays until each subarray contains one element.
// When we merge everything together, we compare the first element of each subarray and put the smaller one in the new
// array, incrementing the subarray from which it comes until subarrays are empty

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

void merge(int array[], int low, int high, int mid, int &comparisons, int &assignments) {

    int sizeHigh = high - mid;
    int sizeLow = mid - low + 1;

    int HiArr[sizeHigh], LoArr[sizeLow];

    for (int i = 0; i < sizeHigh; i++) {
        assignments++;
        HiArr[i] = array[mid + 1 + i];
    } // for
    for (int i = 0; i < sizeLow; i++) {
        assignments++;
        LoArr[i] = array[low + i];
    } // for

    int i =0, j = 0, k = low;
    while (comparisons++ && i < sizeLow && j < sizeHigh) {
        if (LoArr[i] <= HiArr[j]) {
            array[k] = LoArr[i];
            assignments++;
            i++;
        } else {
            array[k] = HiArr[j];
            assignments++;
            j++;
        }
        k++;
    } // while

    while (/* comparisons  ++ && */ i < sizeLow) {
        array[k] = LoArr[i];
        assignments++;
        i++;
        k++;
    }

    while (/* comparisons  ++ && */ j < sizeHigh) {
        array[k] = HiArr[j];
        assignments++;
        j++;
        k++;
    }
}

void mergeSort (int array[], int low, int high, int &comparisons, int &assignments) {

    if (low < high) {
        for (int i = low; i <= high; i++) {
        }

        int mid = (high - low) / 2 + low;

        mergeSort (array, low, mid, comparisons, assignments);
        mergeSort (array, mid + 1, high, comparisons, assignments);

        merge(array, low, high, mid, comparisons, assignments);
    }
}

int main () {
    int comparisons = 0, assignments = 0;
    int arrayay[100];
    fillArray(arrayay, INTY, false);
    mergeSort (arrayay, 0, INTY - 1, comparisons, assignments);
    printArray(arrayay, INTY);
    cout << "Comparisons: " << comparisons << endl;
    cout << "Assignments: " << assignments << endl;

    cout << "n log n: " << INTY * log(INTY) << endl;

    return 0;
}