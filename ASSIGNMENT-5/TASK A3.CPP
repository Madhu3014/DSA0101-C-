#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Bill class
class Bill {
public:
    double amount;
    string type;

    Bill(double a, string t) {
        amount = a;
        type = t;
    }

    double total() const {
        return amount;
    }
};

// Abstract Payer class
class Payer {
public:
    virtual double amountCovered(const Bill& b) const = 0;
    virtual ~Payer() = default;
};

// SelfPay class
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& b) const override {
        return b.total();
    }
};

// Insurance class
class Insurance : public Payer {
    double coverLimit;
    double coPayment;

public:
    Insurance(double limit, double copay)
        : coverLimit(limit), coPayment(copay) {}

    double amountCovered(const Bill& b) const override {
        double amount = b.total() * (1 - coPayment / 100);
        return min(amount, coverLimit);
    }
};

// Government Scheme class
class GovernmentScheme : public Payer {
public:
    double amountCovered(const Bill& b) const override {
        if (b.type == "OP")
            return 1000;
        else if (b.type == "IP")
            return 30000;
        else if (b.type == "DayCare")
            return 12000;
        else if (b.type == "Emergency")
            return 5000;
        else
            return 0;
    }
};

int main() {
    Bill b(40000, "IP");

    SelfPay self;
    Insurance insurance(30000, 20);
    GovernmentScheme govt;

    cout << "Hospital Bill: Rs. " << b.total() << endl;
    cout << "Self Pay Covers: Rs. "
         << self.amountCovered(b) << endl;
    cout << "Insurance Covers: Rs. "
         << insurance.amountCovered(b) << endl;
    cout << "Government Scheme Covers: Rs. "
         << govt.amountCovered(b) << endl;

    return 0;
}
ALTERNATIVE CODES:
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;

class Bill {
public:
    double amount;
    string type;

    Bill(double a, string t) {
        amount = a;
        type = t;
    }
};

// Function type for payment policy
using PaymentPolicy = function<double(const Bill&)>;

int main() {
    Bill b(40000, "IP");

    // Self-pay policy
    PaymentPolicy selfPay = [](const Bill& b) {
        return b.amount;
    };

    // Insurance policy
    double coverLimit = 30000;
    double coPayment = 20;

    PaymentPolicy insurance =
        [coverLimit, coPayment](const Bill& b) {
            double amount =
                b.amount * (1 - coPayment / 100);
            return min(amount, coverLimit);
        };

    // Government scheme policy
    PaymentPolicy government = [](const Bill& b) {
        if (b.type == "IP")
            return 30000.0;
        else if (b.type == "OP")
            return 1000.0;
        else
            return 0.0;
    };

    cout << "Hospital Bill: Rs. "
         << b.amount << endl;

    cout << "Self Pay Covers: Rs. "
         << selfPay(b) << endl;

    cout << "Insurance Covers: Rs. "
         << insurance(b) << endl;

    cout << "Government Scheme Covers: Rs. "
         << government(b) << endl;

    return 0;
}
