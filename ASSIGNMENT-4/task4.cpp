#include <iostream>
using namespace std;

class Account {
public:
    Account() {
        cout << "Account created\n";
    }

    double rate() const {
        return 3.5;
    }

    ~Account() {
        cout << "Account destroyed\n";
    }
};

class SeniorAccount : public Account {
    double* history = new double[100];

public:
    SeniorAccount() {
        cout << "SeniorAccount created\n";
    }

    double rate() const {
        return 4.0;
    }

    ~SeniorAccount() {
        delete[] history;
        cout << "SeniorAccount destroyed\n";
    }
};

int main() {
    Account* a = new SeniorAccount();

    cout << "Interest rate: " << a->rate() << "%\n";

    delete a;

    return 0;
}
PREVENT RECURRENCE:
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual ~Account() {
        cout << "Account destroyed\n";
    }
};

class SeniorAccount : public Account {
    double* history;

public:
    SeniorAccount() {
        history = new double[100];
        cout << "SeniorAccount created\n";
    }

    double rate() const override {
        return 4.0;
    }

    ~SeniorAccount() override {
        delete[] history;
        cout << "SeniorAccount destroyed\n";
    }
};

int main() {
    vector<unique_ptr<Account>> accounts;

    accounts.push_back(make_unique<Account>());
    accounts.push_back(make_unique<SeniorAccount>());

    cout << "Interest Rates:\n";

    for (const auto& a : accounts) {
        cout << a->rate() << "%\n";
    }

    cout << "End of program\n";

    return 0;
}
