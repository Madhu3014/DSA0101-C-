#include <iostream>
using namespace std;

class Event {
    string name;
    int rows, cols, booked;
    char** seats;

public:
    // Dynamic constructor
    Event(string n, int r, int c)
        : name(n), rows(r), cols(c), booked(0), seats(nullptr) {

        if (rows > 0 && cols > 0) {
            seats = new char*[rows];

            for (int i = 0; i < rows; i++) {
                seats[i] = new char[cols];

                for (int j = 0; j < cols; j++)
                    seats[i][j] = 'O';
            }
        }

        cout << "Event created: " << name << endl;
    }

    // Book a seat
    void book(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "Invalid seat\n";
        }
        else if (seats[r][c] == 'X') {
            cout << "Seat already booked\n";
        }
        else {
            seats[r][c] = 'X';
            booked++;
            cout << "Seat booked\n";
        }
    }

    // Cancel a seat
    void cancel(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "Invalid seat\n";
        }
        else if (seats[r][c] == 'O') {
            cout << "Seat is already empty\n";
        }
        else {
            seats[r][c] = 'O';
            booked--;
            cout << "Booking cancelled\n";
        }
    }

    void display() const {
        cout << "\nSeat Map: " << name << endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << seats[i][j] << " ";
            cout << endl;
        }
    }

    // Destructor
    ~Event() {
        for (int i = 0; i < rows; i++)
            delete[] seats[i];

        delete[] seats;

        cout << "Event closed: " << name
             << ", Booked seats: " << booked << endl;
    }

    // Prevent unsafe copying of the owning pointer
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
};

int main() {
    // Stack object
    Event e1("Main Hall", 2, 3);
    e1.book(0, 1);
    e1.book(1, 2);
    e1.cancel(0, 1);
    e1.display();

    // Block-scope object
    {
        Event e2("Small Hall", 2, 2);
        e2.book(0, 0);
        e2.display();
    }

    // Heap object
    Event* e3 = new Event("Open Hall", 2, 2);
    e3->book(1, 1);
    e3->display();
    delete e3;

    // Zero-row event
    Event e4("Empty Hall", 0, 5);
    e4.display();

    return 0;
}
