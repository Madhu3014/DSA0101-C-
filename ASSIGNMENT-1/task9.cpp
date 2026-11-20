
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

const long long MIN_BALANCE = 5000;

long long calculateFare(int zone, int hour)
{
    long long fare;

    if (zone == 1) fare = 1000;
    else if (zone == 2) fare = 2000;
    else if (zone == 3) fare = 3000;
    else return -1;

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak)
        fare += fare * 20 / 100;

    return fare;
}

bool validRecharge(long long amount)
{
    return amount >= 0;
}

bool readHour(string input, int &hour)
{
    stringstream ss(input);
    char extra;

    if (!(ss >> hour) || (ss >> extra))
        return false;

    return hour >= 0 && hour <= 23;
}

void printMoney(long long paise)
{
    cout << "Rs " << paise / 100 << "."
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
}

struct TestCase {
    string name;
    int zone;
    string hour;
    long long balance;
    long long expectedFare;
    bool expectedAllowed;
};

int main()
{
    TestCase tests[] = {
        {"Inner off-peak", 1, "12", 10000, 1000, true},
        {"Middle peak", 2, "9", 10000, 2400, true},
        {"Outer off-peak", 3, "12", 10000, 3000, true},
        {"At 08:00", 1, "8", 10000, 1200, true},
        {"At 10:00", 1, "10", 10000, 1000, true},
        {"At 17:00", 1, "17", 10000, 1200, true},
        {"At 20:00", 1, "20", 10000, 1000, true},
        {"Exactly Rs 50 remains", 1, "12", 6000, 1000, true},
        {"Unknown zone", 4, "12", 10000, -1, false},
        {"Letters for hour", 1, "abc", 10000, -1, false},
        {"Invalid hour", 1, "24", 10000, -1, false}
    };

    int count = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    cout << "METRO FARE TEST REPORT\n\n";

    for (int i = 0; i < count; i++) {
        int hour = 0;
        bool valid = readHour(tests[i].hour, hour);
        long long fare = -1;
        bool allowed = false;

        if (valid) {
            fare = calculateFare(tests[i].zone, hour);

            if (fare >= 0 &&
                tests[i].balance - fare >= MIN_BALANCE) {
                allowed = true;
            }
        }

        bool correct =
            fare == tests[i].expectedFare &&
            allowed == tests[i].expectedAllowed;

        cout << tests[i].name << ": ";

        if (fare >= 0) {
            cout << "Fare = ";
            printMoney(fare);
            cout << ", Journey = "
                 << (allowed ? "Allowed" : "Denied");
        } else {
            cout << "Invalid input or zone";
        }

        cout << " -> " << (correct ? "PASS" : "FAIL")
             << '\n';

        if (correct) passed++;
    }

    cout << "\nTests passed: " << passed
         << "/" << count << '\n';

    cout << "Negative recharge test: "
         << (validRecharge(-100) ? "FAIL" : "PASS")
         << '\n';

    // Five journeys: Inner off-peak, Middle peak,
    // Outer off-peak, Inner peak, Middle off-peak.
    long long fiveJourneyTotal =
        calculateFare(1, 12) +
        calculateFare(2, 9) +
        calculateFare(3, 12) +
        calculateFare(1, 18) +
        calculateFare(2, 12);

    cout << "Five-journey total: ";
    printMoney(fiveJourneyTotal);
    cout << '\n';

    return 0;
}
