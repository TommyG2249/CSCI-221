//
// Created by Thomas Glennon on 3/11/26.
//

#include<iostream>
#include<string>
using namespace std;

string readString () {
    cout << "Please enter a string to be reversed." << endl;
    string s;
    getline(cin,s);
    return s;
}

string reverse(string s, int length) {
    if (length <= 1) {
        string t = "";
        return t + s[length - 1];
    } else {
        return s[length-1] + reverse(s, length-1);
    }
}

int main () {
    string s = readString();
    cout << s << endl;
    cout << reverse(s, s.length()) << endl;
    return 0;
}