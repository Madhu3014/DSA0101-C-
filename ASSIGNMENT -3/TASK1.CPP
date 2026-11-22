#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book {
    string title;
    string author;
    int copies;

public:

    // Default constructor
    Book() : Book("", "Unknown", 0) {}

    // Constructor with title only
    Book(string t) : Book(t, "Unknown", 1) {}

    // Parameterised constructor
    Book(string t, string a, int c)
        : title(t), author(a), copies(c) {
        if (c < 0)
            throw invalid_argument("Invalid number of copies");
    }

    // Display book details
    void display() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Copies: " << copies << endl;
        cout << "------------------" << endl;
    }
};

int main() {
    try {
        // Creating objects using different constructors
        Book b1;
        Book b2("C++ Programming");
        Book b3("Java", "James Gosling", 5);

        cout << "BOOK RECORDS" << endl;

        b1.display();
        b2.display();
        b3.display();

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
