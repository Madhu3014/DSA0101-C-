
#include <iostream>
using namespace std;

const long long MIN_BALANCE = 5000; // Rs 50 in paise

long long calculateFare(int zone, bool peak)
{
    long long fare;

    if (zone == 1)
        fare = 1000;       // Inner: Rs 10
    else if (zone == 2)
        fare = 2000;       // Middle: Rs 20
    else if (zone == 3)
        fare = 3000;       // Outer: Rs 30
    else
        return -1;

    if (peak)
        fare += fare * 20 / 100;

    return fare;
}

// Procedural version
bool canTravel(long long balance, long long fare)
{
    return fare >= 0 && balance - fare >= MIN_BALANCE;
}

void deduct(long long &balance, long long fare)
{
    if (canTravel(balance, fare)) {
        balance -= fare;
        cout << "Journey allowed. Balance: Rs "
             << balance / 100 << '\n';
    } else {
        cout << "Journey denied. Balance: Rs "
             << balance / 100 << '\n';
    }
}

// Object-oriented version
class SmartCard {
private:
    long long balance;

public:
    SmartCard(long long b) : balance(b) {}

    bool canTravel(long long fare) const
    {
        return fare >= 0 &&
               balance - fare >= MIN_BALANCE;
    }

    void deduct(long long fare)
    {
        if (canTravel(fare)) {
            balance -= fare;
            cout << "Journey allowed. Balance: Rs "
                 << balance / 100 << '\n';
        } else {
            cout << "Journey denied. Balance: Rs "
                 << balance / 100 << '\n';
        }
    }
};

int main()
{
    cout << "PROCEDURAL VERSION\n";
    long long balance = 10000;

    deduct(balance, calculateFare(3, true));
    deduct(balance, calculateFare(2, false));

    cout << "\nOBJECT-ORIENTED VERSION\n";
    SmartCard card(10000);

    card.deduct(calculateFare(3, true));
    card.deduct(calculateFare(2, false));

    return 0;
}
