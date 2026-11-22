
#include <iostream>
using namespace std;

struct Parcel {
    int grams;
    bool express;
    bool insured;
};

void charge(double kg, bool express = false,
            bool insured = false) {
    int amount = 50 + static_cast<int>(kg * 40);

    if (express) amount += 30;
    if (insured) amount += 20;

    cout << "Kg: " << kg << " - Rs. " << amount << endl;
}

// Parcel object
void charge(const Parcel& p) {
    charge(p.grams, p.express, p.insured);
}

int main() {
    Parcel p = {750, true, true};

    charge(2);
    charge(1.5);
    charge(p);
    charge(2, true);
    charge(2.0f);
    charge(1000, false, true);

    return 0;
}
