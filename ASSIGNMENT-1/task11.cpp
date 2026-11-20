
#include <iostream>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer };

constexpr long long BASE_PAISE[] = {
    1000, 2000, 3000
};

constexpr int PEAK_PERCENT = 20;
constexpr long long MIN_BALANCE = 5000;

bool isPeak(int hour)
{
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

long long calculateFare(Zone zone, int hour)
{
    int index = static_cast<int>(zone);
    long long fare = BASE_PAISE[index];

    if (isPeak(hour))
        fare += fare * PEAK_PERCENT / 100;

    return fare;
}

class SmartCard
{
private:
    long long balance;

public:
    explicit SmartCard(long long initialBalance)
        : balance(initialBalance) {}

    bool canTravel(long long fare) const
    {
        return fare >= 0 &&
               balance - fare >= MIN_BALANCE;
    }

    bool deduct(long long fare)
    {
        if (!canTravel(fare))
            return false;

        balance -= fare;
        return true;
    }

    long long getBalance() const
    {
        return balance;
    }
};

void printMoney(long long paise)
{
    cout << "Rs " << paise / 100 << "."
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
}

int main()
{
    cout << "TASK 11: FINAL DESIGN\n\n";

    SmartCard card(10000); // Rs 100.00

    struct Trip {
        Zone zone;
        int hour;
    };

    Trip trips[] = {
        {Zone::Inner, 12},
        {Zone::Middle, 9},
        {Zone::Outer, 12}
    };

    const int count = sizeof(trips) / sizeof(trips[0]);

    for (int i = 0; i < count; i++) {
        long long fare = calculateFare(
            trips[i].zone, trips[i].hour
        );

        cout << "Journey " << i + 1 << " fare: ";
        printMoney(fare);

        if (card.deduct(fare)) {
            cout << " | Allowed";
        } else {
            cout << " | Denied";
        }

        cout << " | Balance: ";
        printMoney(card.getBalance());
        cout << '\n';
    }

    // Network-scale arithmetic experiment
    long long journeys = 3000000LL;
    long long farePerJourney = 3000LL;
    long long networkTotal = journeys * farePerJourney;

    cout << "\nNetwork-scale example:\n";
    cout << journeys << " journeys at Rs 30 each = ";
    printMoney(networkTotal);
    cout << '\n';

    cout << "\nRecommended: integer paise, long long, "
         << "central constants, private card balance.\n";

    return 0;
}
