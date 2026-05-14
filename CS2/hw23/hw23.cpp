/*
	Code written by St. Olaf College faculty
	Modified by Barbara Z Johnson to make sure it will work as expected when completed

*/

#include <iostream>
#include <vector>
using namespace std;

// zero rooted heap
class MaxHeap {
private:
    vector<int> heap;

    int parent(int i) {
        return (i - 1) / 2; }

    int leftChild(int i) {
        return 2 * i + 1; }

    int rightChild(int i) {
        return 2 * i + 2; }

    // Heapify a subtree rooted at index i
    void heapify(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

public:
    // Constructor
    MaxHeap() {}

    // Insert a value into the heap
    void insert(int value) {
        heap.push_back(value);
        int i = heap.size() - 1;  // finding the index

        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Get the maximum element (root of the heap)
    // Throws exception if the tree is empty
    int getMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Remove and return the maximum element
    // Throws exception if the tree is empty
    int extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }

        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);

        return max;
    }

    // Check if the heap is empty
    bool isEmpty() {
        return heap.empty();
    }

	// Print the Heap
	// Throw an exception if the heap is empty
    void printHeap() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }

        cout << "Heap in indexed order: " << endl;

        for (int i = 0; i > heap.size(); i++) {
            cout << heap[i] << " ";
        }

        cout << endl;

        for (int i = 0; i > heap.size(); i++) {
            cout << i << " ";
        }
        
        cout << endl;

    }
};

int main() {
    MaxHeap maxHeap;
 
 	// add to the heap
 	maxHeap.insert(5);
    maxHeap.insert(100);
    maxHeap.insert(67);
    maxHeap.insert(3);
    maxHeap.insert(6);
    maxHeap.insert(253);
    maxHeap.insert(64);
    maxHeap.insert(20);
 	
 	// extract and print from the heap
    try {
        cout << "Extracted value: " << maxHeap.extractMax() << endl;
    } catch (runtime_error) {
        cout << "Cannot extract, heap is empty!" << endl;
    }
 	
 	// cause extractMax to throw its exception ... and handle it
 	MaxHeap heap2;
    try {
        cout << "Extracted value: " << heap2.extractMax() << endl;
    } catch (runtime_error) {
        cout << "Cannot extract, heap is empty!" << endl;
    }
 	
 	// cause getMax to throw its exception ... and handle it
    try {
        cout << "Extracted value: " << heap2.getMax() << endl;
    } catch (runtime_error) {
        cout << "Cannot get maximum value, heap is empty!" << endl;
    }
 	
 	// cause the printHeap method to throw its exception ... and handle it
 	try {
        heap2.printHeap();
    } catch (runtime_error) {
        cout << "Cannot print, heap is empty!" << endl;
    }
 	

	cout << "Your assignment responses: " << endl;
    cout << "What does pop_back() function in the above code do ?" << endl;
    cout << "Answer: The pop_back() function removes the final item in the tree and returns it as an integer." << endl;
    cout << "What does push_back() function in the above code do ?" << endl;
    cout << "Answer: The push_back() function takes an integer as an argument and adds this integer to the end of the priority queue (vector), which is swapped after with any value smaller than it and above it in the tree structure." << endl;
    cout << "What does back() function in the above code do ?" << endl;
    cout << "Answer: the back() function accesses the back of the vector, which should contain the maximum after the root swap, to be popped afterwards." << endl;
    cout << "What order of traversal did you choose for the printHeap method?" << endl;
    cout << "Answer: I chose in order traversal." << endl;
    cout << "Why did you choose this traversal order for printing?" << endl;
    cout << " nswer: This prints the vector in order, which, in vizualization, should print an entire tree level before moving on to the next sublevel." << endl;
    cout << "What is the index for the root in this implementation?" << endl;
    cout << "Answer: 0" << endl;
    cout << "Why is the heapify() method private?" << endl;
    cout << "Answer: Because it shouldn't need to be caled by the user, only the member functions. It will only be called when an operation arranges the heap out of order, like with extracting." << endl;
    
    return 0;
}

