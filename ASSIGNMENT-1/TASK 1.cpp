
#include <iostream>
using namespace std;

class SmartCard {
private:
    int balance;

public:
    SmartCard(int b) {
        balance = b;
    }

    bool canTravel(int fare) {
        return (balance - fare) >= 5000;
    }

    void deductFare(int fare) {
        if (canTravel(fare)) {
            balance -= fare;
            cout << "Journey allowed" << endl;
        } else {
            cout << "Journey denied" << endl;
        }
    }

    void displayBalance() {
        cout << "Balance: Rs " << balance / 100.0 << endl;
    }
};

int main() {
    SmartCard card(10000);

    card.deductFare(1000);
    card.displayBalance();

    return 0;
}
