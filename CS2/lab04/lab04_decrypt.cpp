//
// Created by Thomas Glennon on 3/16/26.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string readFile(string fileName) {
    ifstream fin;
    fin.open(fileName);
    if (!fin.is_open()) {
        cout << "File cannot be opened." << endl;
        return "";
    }
    string s = "";
    char c;
    while (fin.get(c)) {
        s = s + c;
    };
    fin.close();
    return s;
}

void writeFile(string fileName, string contents) {
    ofstream fout;
    string fileNameEnc = "Decrypted_" + fileName;
    fout.open(fileNameEnc);
    if (!fout.is_open()) {
        cout << "File cannot be opened." << endl;
    }
    fout << contents;
    fout.close();
}

int getKey() {
    int key;
    cout << "Enter an integer as your Caesar cipher key: " << endl;

    while (!(cin >> key)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter an integer." << endl;
    }
    return key;
}

char convertChar(char c, int key) {
    int c_int = (int)c;
    char c_converted;
    if (c_int >= 97 && c_int <= 122) {
        int base = (int)'a';
        c_int -= base;
        c_int -= key;
        c_int = c_int % 26;
        if (c_int < 0) c_int += 26;
        c_int += base;
        c_converted = (char)c_int;
    } else if (c_int >= 65 && c_int <= 90) {
        int base = (int)'A';
        c_int -= base;
        c_int -= key;
        c_int = c_int % 26;
        if (c_int < 0) c_int += 26;
        c_int += base;
        c_converted = (char)c_int;
    } else {
        c_converted = (char)c_int;
    }
    return c_converted;
}

string decryptString(string s, int key) {
    string decrypted = "";
    for (int i = 0; i < s.length(); i++) {
        decrypted += convertChar(s[i], key);
    }
    return decrypted;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please provide at least one file to read from." << endl;
        return 1;
    }

    string fileName = argv[1];
    string datatoDec = readFile(fileName);

    int key = getKey();

    string decrypted = decryptString(datatoDec, key);

    writeFile(fileName, decrypted);
    return 0;
}