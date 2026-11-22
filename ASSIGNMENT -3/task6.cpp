#include <iostream>
#include <cstring>
using namespace std;

class Text {
    char* data;

public:
    // Constructor
    Text(const char* s = "") {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    // Copy constructor
    Text(const Text& t) {
        data = new char[strlen(t.data) + 1];
        strcpy(data, t.data);
    }

    // Copy assignment
    Text& operator=(const Text& t) {
        if (this != &t) {
            char* temp = new char[strlen(t.data) + 1];
            strcpy(temp, t.data);
            delete[] data;
            data = temp;
        }
        return *this;
    }

    // Concatenation
    Text operator+(const Text& t) const {
        char* temp = new char[strlen(data) + strlen(t.data) + 1];
        strcpy(temp, data);
        strcat(temp, t.data);

        Text result(temp);
        delete[] temp;
        return result;
    }

    // Equality
    bool operator==(const Text& t) const {
        return strcmp(data, t.data) == 0;
    }

    // Inequality
    bool operator!=(const Text& t) const {
        return !(*this == t);
    }

    // Printing
    friend ostream& operator<<(ostream& out, const Text& t) {
        out << t.data;
        return out;
    }

    // Destructor
    ~Text() {
        delete[] data;
    }
};

int main() {
    Text a("Hello ");
    Text b("World");

    Text c = a + b;

    cout << "Message: " << c << endl;
    cout << boolalpha;
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;

    Text d = a;
    cout << "Copied text: " << d << endl;

    d = b;
    cout << "Assigned text: " << d << endl;

    d = d;
    cout << "Self assignment: " << d << endl;

    Text empty("");
    cout << "Empty text: [" << empty << "]" << endl;

    Text longText("This is a longer SMS message.");
    cout << "Long text: " << longText << endl;
}
ALTERNATIVE CONCEPT
#include <string>
using namespace std;

class Text {
    string data;

public:
    Text(string s = "") : data(s) {}

    Text operator+(const Text& t) const {
        return Text(data + t.data);
    }

    bool operator==(const Text& t) const {
        return data == t.data;
    }

    bool operator!=(const Text& t) const {
        return data != t.data;
    }
};
