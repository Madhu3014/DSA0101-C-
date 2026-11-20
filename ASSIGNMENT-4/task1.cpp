
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// Named constant instead of magic number
constexpr double ALLOWANCE_RATE = 0.42;

// Base class
class Staff {
protected:
    string name;
    int id;

public:
    Staff(string n, int i) : name(n), id(i) {}

    virtual double pay() const = 0;

    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }

    virtual ~Staff() = default;
};

// Derived class 1
class Professor : public Staff {
private:
    double basic;
    double research;

public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}

    double pay() const override {
        return basic + basic * ALLOWANCE_RATE + research;
    }
};

// Derived class 2
class LabAssistant : public Staff {
private:
    double basic;

public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i), basic(b) {}

    double pay() const override {
        return basic + basic * ALLOWANCE_RATE;
    }
};

// Derived class 3
class GuestFaculty : public Staff {
private:
    double hours;
    double rate;

public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i), hours(h), rate(r) {}

    double pay() const override {
        return hours * rate;
    }
};

int main() {
    vector<unique_ptr<Staff>> staffList;

    staffList.push_back(
        make_unique<Professor>("Arun", 101, 50000, 5000));

    staffList.push_back(
        make_unique<LabAssistant>("Kumar", 102, 30000));

    staffList.push_back(
        make_unique<GuestFaculty>("Priya", 103, 40, 500));

    cout << "COLLEGE PAYROLL SYSTEM\n";
    cout << "----------------------\n";

    for (const auto& staff : staffList) {
        staff->display();
        cout << "Pay: " << staff->pay() << endl;
        cout << "----------------------\n";
    }

    return 0;
}
