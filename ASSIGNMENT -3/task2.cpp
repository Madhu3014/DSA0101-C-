#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;

public:
    // Constructor
    explicit Prescription(int count)
        : n(count), medicines(new std::string[count]) {}

    // TODO 1: Deep copy constructor
    Prescription(const Prescription& other)
        : n(other.n), medicines(new std::string[other.n]) {
        for (int i = 0; i < n; i++)
            medicines[i] = other.medicines[i];
    }

    // TODO 2: Copy assignment operator
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* temp = new std::string[other.n];

            for (int i = 0; i < other.n; i++)
                temp[i] = other.medicines[i];

            delete[] medicines;
            medicines = temp;
            n = other.n;
        }
        return *this;
    }

    // TODO 3: Destructor
    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const std::string& m) {
        if (i >= 0 && i < n)
            medicines[i] = m;
    }

    std::string get(int i) const {
        if (i >= 0 && i < n)
            return medicines[i];
        return "";
    }
};

int main() {
    Prescription p(2);

    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;  // Copy constructor
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;               // Copy assignment

    p.set(0, "Ibuprofen");

    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';

    return 0;
}
ALTERNATIVE CONCEPT
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Prescription {
    vector<string> medicines;

public:
    Prescription(int n) : medicines(n) {}

    void set(int i, string m) {
        if (i >= 0 && i < medicines.size())
            medicines[i] = m;
    }

    string get(int i) const {
        if (i >= 0 && i < medicines.size())
            return medicines[i];
        return "";
    }
};
