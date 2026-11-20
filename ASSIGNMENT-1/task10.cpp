
#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    long long journeys[] = {20000, 500000, 3000000};

    const long long PAISE_PER_TRIP = 10;
    const double RUPEES_PER_TRIP = 0.10;

    cout << fixed << setprecision(15);
    cout << "TASK 10: EXPECTED VS ACTUAL\n\n";

    for (long long n : journeys) {
        long long integerPaise = n * PAISE_PER_TRIP;

        double doubleTotal = 0.0;
        for (long long i = 0; i < n; i++) {
            doubleTotal += RUPEES_PER_TRIP;
        }

        double expected = n / 10.0;

        cout << "Journeys: " << n << '\n';
        cout << "Expected total: Rs " << expected << '\n';
        cout << "Double total:   Rs " << doubleTotal << '\n';
        cout << "Integer total:  " << integerPaise
             << " paise\n";
        cout << "Double error:   "
             << doubleTotal - expected << " rupees\n\n";
    }

    cout << "Typical 32-bit int maximum: "
         << INT_MAX << '\n';

    long long networkPaise = 3000000LL * 3000LL;

    cout << "3,000,000 journeys at Rs 30 each: "
         << networkPaise << " paise\n";

    if (networkPaise > INT_MAX)
        cout << "Result: This total exceeds a typical int range.\n";

    cout << "Use long long for large integer-paise totals.\n";

    return 0;
}
