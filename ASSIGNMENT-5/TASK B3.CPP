
#include <iostream>
#include <vector>
#include <memory>
#include <variant>
using namespace std;

struct OutPatientBill {
    double consultation, tests;
    double total() const { return consultation + tests; }
};

struct InPatientBill {
    double roomRate, days, treatment;
    double total() const { return roomRate * days + treatment; }
};

// (a) Virtual function approach
struct BaseBill {
    virtual double total() const = 0;
    virtual ~BaseBill() = default;
};

struct OutVirtual : BaseBill {
    double consultation, tests;
    OutVirtual(double a, double b) : consultation(a), tests(b) {}
    double total() const override { return consultation + tests; }
};

struct InVirtual : BaseBill {
    double roomRate, days, treatment;
    InVirtual(double a, double b, double c)
        : roomRate(a), days(b), treatment(c) {}
    double total() const override { return roomRate * days + treatment; }
};

// (b) Single Bill struct and switch
struct Bill {
    int type; // 0 = outpatient, 1 = inpatient
    double a, b, c;
};

double switchTotal(const Bill& x) {
    switch (x.type) {
        case 0: return x.a + x.b;
        case 1: return x.a * x.b + x.c;
        default: return 0;
    }
}

// (c) Variant approach
using VariantBill = variant<OutPatientBill, InPatientBill>;

double variantTotal(const VariantBill& b) {
    return visit([](const auto& x) { return x.total(); }, b);
}

int main() {
    vector<unique_ptr<BaseBill>> virtualBills;
    vector<Bill> switchBills;
    vector<VariantBill> variantBills;

    // Ten sample bills: five outpatient and five inpatient
    vector<Bill> data = {
        {0, 500, 300, 0},
        {1, 1000, 2, 1500},
        {0, 600, 400, 0},
        {1, 1200, 3, 2000},
        {0, 700, 250, 0},
        {1, 900, 2, 1800},
        {0, 800, 350, 0},
        {1, 1500, 2, 2500},
        {0, 550, 450, 0},
        {1, 1100, 3, 2200}
    };

    for (const auto& x : data) {
        switchBills.push_back(x);

        if (x.type == 0) {
            virtualBills.push_back(
                make_unique<OutVirtual>(x.a, x.b));
            variantBills.push_back(OutPatientBill{x.a, x.b});
        } else {
            virtualBills.push_back(
                make_unique<InVirtual>(x.a, x.b, x.c));
            variantBills.push_back(InPatientBill{x.a, x.b, x.c});
        }
    }

    double vTotal = 0, sTotal = 0, varTotal = 0;

    for (const auto& b : virtualBills) vTotal += b->total();
    for (const auto& b : switchBills) sTotal += switchTotal(b);
    for (const auto& b : variantBills) varTotal += variantTotal(b);

    cout << "Virtual total: " << vTotal << '\n';
    cout << "Switch total: " << sTotal << '\n';
    cout << "Variant total: " << varTotal << '\n';

    cout << boolalpha
         << "All totals agree: "
         << (vTotal == sTotal && sTotal == varTotal) << '\n';
}
COMPARISON CODE:

#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>
using namespace std;
using namespace chrono;

bool validateReturn(double amount) {
    return amount >= 0;
}

void validateException(double amount) {
    if (amount < 0)
        throw invalid_argument("negative amount");
}

template<class Function>
double timeIt(Function f) {
    auto start = steady_clock::now();
    volatile long long result = f();
    auto finish = steady_clock::now();

    cout << "Valid count: " << result << '\n';
    return duration<double, milli>(finish - start).count();
}

int main() {
    const int N = 1000000;

    for (int invalidPercent : {0, 1, 50}) {
        vector<double> bills(N, 100.0);

        int invalidCount = N * invalidPercent / 100;
        for (int i = 0; i < invalidCount; ++i)
            bills[i] = -10.0;

        cout << "\nInvalid: " << invalidPercent << "%\n";

        double returnTime = timeIt([&]() {
            long long valid = 0;
            for (double x : bills)
                if (validateReturn(x)) ++valid;
            return valid;
        });

        double exceptionTime = timeIt([&]() {
            long long valid = 0;
            for (double x : bills) {
                try {
                    validateException(x);
                    ++valid;
                } catch (const invalid_argument&) {
                    // Invalid bill is rejected.
                }
            }
            return valid;
        });

        cout << "Return-code time: " << returnTime << " ms\n";
        cout << "Exception time:   " << exceptionTime << " ms\n";
    }
}
