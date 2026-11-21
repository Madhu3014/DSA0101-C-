
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
using namespace std;

// Existing bill interface
class Bill {
public:
    virtual double calculate() const = 0;
    virtual ~Bill() = default;
};

// Existing bill type
class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(double c, double t)
        : consultation(c), tests(t) {}

    double calculate() const override {
        return consultation + tests;
    }
};

// Existing bill type
class InPatientBill : public Bill {
    double roomRate, days, treatment;
public:
    InPatientBill(double r, double d, double t)
        : roomRate(r), days(d), treatment(t) {}

    double calculate() const override {
        return roomRate * days + treatment;
    }
};

// NEW bill type: existing classes are not modified
class DayCareBill : public Bill {
    double procedureFee, facilityFee;
public:
    DayCareBill(double p, double f)
        : procedureFee(p), facilityFee(f) {}

    double calculate() const override {
        return procedureFee + facilityFee;
    }
};

// Payer interface
class Payer {
public:
    virtual double pay(double billAmount) const = 0;
    virtual ~Payer() = default;
};

// Existing payer
class StandardPayer : public Payer {
public:
    double pay(double amount) const override {
        return amount * 0.80;
    }
};

// NEW payer
class CommunityHealthPayer : public Payer {
public:
    double pay(double amount) const override {
        return amount * 0.90;
    }
};

int main() {
    try {
        vector<unique_ptr<Bill>> bills;

        bills.push_back(make_unique<OutPatientBill>(500, 300));
        bills.push_back(make_unique<InPatientBill>(1000, 2, 1500));
        bills.push_back(make_unique<DayCareBill>(2500, 500));

        StandardPayer standard;
        CommunityHealthPayer community;

        for (const auto& bill : bills) {
            double amount = bill->calculate();

            if (amount < 0)
                throw invalid_argument("Negative bill amount");

            cout << "Bill amount: " << amount << '\n';
            cout << "Standard payer: "
                 << standard.pay(amount) << '\n';
            cout << "Community payer: "
                 << community.pay(amount) << '\n';
        }

        cout << "All tests completed successfully\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }
}
