//
// Created by Thomas Glennon on 3/24/26.
//
// I got the input validation code from https://www.geeksforgeeks.org/cpp/how-to-validate-user-input-in-cpp/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Stack {
private:
    int size;
    int topStack;
    vector<int> vector;
public:
    Stack() {
        size = 0;
        topStack = 0;
    } // constructor

    void push(int element) {
        vector.push_back(element);
        size++;
        topStack = size - 1;
    } // push

    int pop() {
        if (size == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        } // if

        int result = vector[topStack];
        topStack--;
        size--;
        return result;
    } // pop

    int top() {
        if (size == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        } else if (topStack < 0) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return vector[topStack];
    } // top

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }
};

string decimalToBinary(short number) {
    Stack stack;
    short base = 2;
    while (number > 0) {
        int remainder = number % base;
        stack.push(remainder);
        number = number / base;
    }
    string result;
    while (!stack.isEmpty()) {
        result += to_string(stack.pop());
    }

    while (result.length() < 16) {
        result = "0" + result;
    }

    result.insert(12, " ");
    result.insert(8, " ");
    result.insert(4, " ");

    return result;
}

bool inputCheck (short input) {
    bool result = false;
    for (int i = 0; i < 17; i++) {
        if (input >= 0 && input <= 32767) {
            result = true;
        }
    }
    return result;
}

short inputWrapper(string message) {
    short input = 0;
    cout << message << endl;
    bool pass = false;
    while (pass == false) {
        if (!(cin >> input)) {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message << endl;
        } else if (!(inputCheck(input))) {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << message << endl;
        } else {
            pass = true;
        } // else
    } // while
    return input;
}

int main () {
    short input;
    input = inputWrapper("Please enter a number between 0 and 32767");
    cout << decimalToBinary(input) << endl;
}