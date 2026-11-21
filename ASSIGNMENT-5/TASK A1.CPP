
#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
class Bill {
protected:
    string patient;

public:
    Bill(string p) : patient(p) {}

    // Pure virtual functions
    virtual double total() const = 0;
    virtual string type() const = 0;

    // Common function
    void print() const {
        cout << type() << " Bill - "
             << patient << " : Rs. "
             << total() << endl;
    }

    // Virtual destructor
    virtual ~Bill() {}
};

// Derived Class 1
class OutPatientBill : public Bill {
    double consultation, tests;

public:
    OutPatientBill(string p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}

    double total() const override {
        return consultation + tests;
    }

    string type() const override {
        return "OutPatient";
    }
};

// Derived Class 2
class InPatientBill : public Bill {
    int days;
    double perDay, procedures, medicines;

public:
    InPatientBill(string p, int d, double rate,
                  double proc, double med)
        : Bill(p), days(d), perDay(rate),
          procedures(proc), medicines(med) {}

    double total() const override {
        return days * perDay + procedures + medicines;
    }

    string type() const override {
        return "InPatient";
    }
};

// Derived Class 3
class DayCareBill : public Bill {
    double packagePrice;

public:
    DayCareBill(string p, double price)
        : Bill(p), packagePrice(price) {}

    double total() const override {
        return packagePrice;
    }

    string type() const override {
        return "DayCare";
    }
};

// Derived Class 4
class EmergencyBill : public Bill {
    double baseCharge, hourlyCharge;
    int hours;

public:
    EmergencyBill(string p, double base,
                  double hourly, int h)
        : Bill(p), baseCharge(base),
          hourlyCharge(hourly), hours(h) {}

    double total() const override {
        return baseCharge + hourlyCharge * hours;
    }

    string type() const override {
        return "Emergency";
    }
};

// Main Function
int main() {

    Bill* bills[] = {
        new OutPatientBill("Ravi", 500, 1200),
        new InPatientBill("Meena", 3, 2500, 10000, 5000),
        new DayCareBill("Arun", 15000),
        new EmergencyBill("Priya", 2000, 500, 4)
    };

    double grandTotal = 0;

    cout << "HOSPITAL BILLING SYSTEM" << endl;
    cout << "-----------------------" << endl;

    for (Bill* b : bills) {
        b->print();
        grandTotal += b->total();
    }

    cout << "-----------------------" << endl;
    cout << "Grand Total: Rs. "
         << grandTotal << endl;

    // Delete all objects
    for (Bill* b : bills) {
        delete b;
    }

    return 0;
}
ALTERNATIVE CONCEPT:
struct Bill {
    int type;
    double amount1, amount2;
    int days;
};

double total(Bill b) {
    switch (b.type) {
        case 1:
            return b.amount1 + b.amount2;

        case 2:
            return b.days * b.amount1 + b.amount2;

        case 3:
            return b.amount1;

        case 4:
            return b.amount1 + b.amount2 * b.days;

        default:
            return 0;
    }
}
