
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int readNumber(const string& prompt)
{
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            return value;
        }

        cout << "Invalid input! Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printMoney(long long paise)
{
    cout << "Rs " << paise / 100 << "."
         << setw(2) << setfill('0') << paise % 100
         << setfill(' ');
}

int main()
{
    int zone, hour, balanceRupees;

    cout << "METRO SMART-CARD GATE\n";

    zone = readNumber("Enter zone (1=Inner, 2=Middle, 3=Outer): ");
    hour = readNumber("Enter journey hour (0-23): ");
    balanceRupees = readNumber("Enter card balance in rupees: ");

    if (zone < 1 || zone > 3 ||
        hour < 0 || hour > 23 || balanceRupees < 0) {
        cout << "Invalid zone, hour, or balance.\n";
        return 0;
    }

    long long fare;

    if (zone == 1)
        fare = 1000;
    else if (zone == 2)
        fare = 2000;
    else
        fare = 3000;

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak)
        fare += fare * 20 / 100;

    long long balance = static_cast<long long>(balanceRupees) * 100;

    cout << "\n--- JOURNEY REPORT ---\n";
    cout << "Zone: "
         << (zone == 1 ? "Inner" :
             zone == 2 ? "Middle" : "Outer") << '\n';

    cout << "Peak hour: " << (peak ? "Yes" : "No") << '\n';
    cout << "Fare: ";
    printMoney(fare);
    cout << '\n';

    if (balance - fare >= 5000) {
        balance -= fare;
        cout << "Journey: Allowed\n";
    } else {
        cout << "Journey: Denied (minimum Rs 50 must remain)\n";
    }

    cout << "Remaining balance: ";
    printMoney(balance);
    cout << '\n';

    return 0;
}
