
#include <iostream>
using namespace std;

enum class Zone { Inner, Middle, Outer };

constexpr int INNER_FARE = 1000;
constexpr int MIDDLE_FARE = 2000;
constexpr int OUTER_FARE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

int main() {
    Zone z = Zone::Outer;
    int fare = OUTER_FARE;

    cout << "Inner fare: " << INNER_FARE << " paise\n";
    cout << "Middle fare: " << MIDDLE_FARE << " paise\n";
    cout << "Outer fare: " << fare << " paise\n";
    cout << "Peak surcharge: "
         << PEAK_SURCHARGE_PERCENT << "%\n";
    cout << "Minimum balance: "
         << MIN_BALANCE_PAISE << " paise\n";

    if (z == Zone::Outer) {
        cout << "Selected zone: Outer\n";
    }

    return 0;
}
