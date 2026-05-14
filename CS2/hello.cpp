// Tommy Glennon - 1:42pm, 02/27/26
// HW7
#include <iostream>
#include <string>
using namespace std;

class Person {
    private:

        string name;

    public:

        Person(string str) {
            name = str;
        }

        void greet() {
            cout << "Hello, " << name << "!" << endl;
        }


};

int main() {

    string str;
    cout << "Enter a name: " << endl;
    getline(cin, str);
    Person user(str);
    user.greet();

    return 0;
}