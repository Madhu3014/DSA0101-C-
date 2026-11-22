
#include <iostream>
#include <iomanip>
using namespace std;

class Cart {
    double amount;

public:
    Cart(double a) {
        amount = a;
    }

    double total() const {
        return amount;
    }
};

int main() {
    Cart c1(250);
    Cart c2(450);
    Cart c3(350);

    Cart* carts[3] = {&c1, &c2, &c3};

    Cart* highest = carts[0];

    for (int i = 1; i < 3; i++) {
        if (carts[i]->total() > highest->total()) {
            highest = carts[i];
        }
    }

    cout << fixed << setprecision(2);
    cout << "Highest Cart Total: "
         << highest->total() << endl;

    return 0;
}

  
ALTERNATIVE CONCEPT:

#include <iostream>
#include <iomanip>
using namespace std;

class Cart {
    double amount;

public:
    Cart(double a) {
        amount = a;
    }

    double total() const {
        return amount;
    }
};

int main() {
    Cart c1(250);
    Cart c2(450);
    Cart c3(350);

    Cart* carts[3] = {&c1, &c2, &c3};

    Cart* highest = carts[0];

    for (int i = 1; i < 3; i++) {
        if (carts[i]->total() > highest->total()) {
            highest = carts[i];
        }
    }

    cout << fixed << setprecision(2);
    cout << "Highest Cart Total: "
         << highest->total() << endl;

    return 0;
}


FINAL OUTPPPPUT
