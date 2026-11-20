
#include <iostream>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };

constexpr long long BASE_FARE_PAISE[] = {
    1000, 2000, 3000, 6000
};

constexpr long long MIN_BALANCE = 5000;

bool isPeak(int hour)
{
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

const char* zoneName(Zone zone)
{
    switch (zone) {
        case Zone::Inner:   return "Inner";
        case Zone::Middle:  return "Middle";
        case Zone::Outer:   return "Outer";
        case Zone::Airport: return "Airport";
    }
    return "Invalid";
}

long long calculateFare(Zone zone, int hour, bool weekend)
{
    if (hour < 0 || hour > 23)
        return -1;

    int index = static_cast<int>(zone);
    long long fare = BASE_FARE_PAISE[index];

    // Weekend discount replaces the peak surcharge.
    if (weekend)
        fare -= fare * 10 / 100;
    else if (isPeak(hour))
        fare += fare * 20 / 100;

    return fare;
}

void printMoney(long long paise)
{
    cout << "Rs " << paise / 100 << "."
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
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
               balance >= fare &&
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

class Pass
{
private:
    Zone firstZone;
    Zone secondZone;

public:
    Pass(Zone first, Zone second)
        : firstZone(first), secondZone(second) {}

    bool covers(Zone zone) const
    {
        return zone == firstZone || zone == secondZone;
    }
};

void showFare(const char* description,
              Zone zone, int hour, bool weekend)
{
    cout << description << ": ";
    long long fare = calculateFare(zone, hour, weekend);

    if (fare < 0) {
        cout << "Invalid hour\n";
        return;
    }

    printMoney(fare);
    cout << '\n';
}

void processJourney(SmartCard& card, const Pass& pass,
                    Zone zone, int hour, bool weekend)
{
    cout << zoneName(zone) << ": ";

    if (hour < 0 || hour > 23) {
        cout << "Invalid hour | Journey rejected\n";
        return;
    }

    if (pass.covers(zone)) {
        cout << "Pass covered | Fare Rs 0.00 | Balance ";
        printMoney(card.getBalance());
        cout << '\n';
        return;
    }

    long long fare = calculateFare(zone, hour, weekend);

    cout << "Fare ";
    printMoney(fare);

    if (card.deduct(fare)) {
        cout << " | Allowed | Balance ";
    } else {
        cout << " | Denied | Balance ";
    }

    printMoney(card.getBalance());
    cout << '\n';
}

int main()
{
    cout << fixed;

    cout << "TASK 12: REVISED METRO FARE SYSTEM\n\n";

    cout << "FARE RULE TESTS\n";
    showFare("Inner weekday off-peak",
             Zone::Inner, 12, false);
    showFare("Middle weekday peak",
             Zone::Middle, 9, false);
    showFare("Airport weekday peak",
             Zone::Airport, 9, false);
    showFare("Airport weekend at peak hour",
             Zone::Airport, 18, true);
    showFare("Outer weekend off-peak",
             Zone::Outer, 12, true);

    cout << "\nMONTHLY PASS TESTS\n";

    // Pass permits unlimited journeys in Inner and Airport.
    Pass monthlyPass(Zone::Inner, Zone::Airport);
    SmartCard card(20000); // Rs 200.00

    processJourney(card, monthlyPass,
                   Zone::Inner, 12, false);
    processJourney(card, monthlyPass,
                   Zone::Middle, 9, false);
    processJourney(card, monthlyPass,
                   Zone::Airport, 18, true);

    cout << "\nMINIMUM BALANCE TESTS\n";

    SmartCard exactCard(6000); // Rs 60.00
    bool exactAllowed =
        exactCard.deduct(calculateFare(Zone::Inner, 12, false));

    cout << "Rs 60 balance, Rs 10 fare: "
         << (exactAllowed ? "Allowed" : "Denied")
         << " | Balance ";
    printMoney(exactCard.getBalance());
    cout << '\n';

    SmartCard lowCard(6000); // Rs 60.00
    bool lowAllowed =
        lowCard.deduct(calculateFare(Zone::Outer, 12, false));

    cout << "Rs 60 balance, Rs 30 fare: "
         << (lowAllowed ? "Allowed" : "Denied")
         << " | Balance ";
    printMoney(lowCard.getBalance());
    cout << '\n';

    cout << "\nINVALID INPUT TEST\n";
    showFare("Invalid hour",
             Zone::Inner, 25, false);

    return 0;
}
