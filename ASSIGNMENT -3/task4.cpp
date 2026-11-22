#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    // Addition
    Money operator+(const Money& m) const {
        return Money(0, paise + m.paise);
    }

    // Subtraction
    Money operator-(const Money& m) const {
        return Money(0, paise - m.paise);
    }

    // Addition assignment
    Money& operator+=(const Money& m) {
        paise += m.paise;
        return *this;
    }

    // Equality
    bool operator==(const Money& m) const {
        return paise == m.paise;
    }

    // Less than
    bool operator<(const Money& m) const {
        return paise < m.paise;
    }

    // Output
    friend ostream& operator<<(ostream& out, const Money& m) {
        long long value = m.paise;
        out << "Rs ";

        if (value < 0) {
            out << "-";
            value = -value;
        }

        out << value / 100 << "."
            << setw(2) << setfill('0') << value % 100;
        return out;
    }

    // Input: enter rupees and paise separately
    friend istream& operator>>(istream& in, Money& m) {
        long long r;
        int p;
        in >> r >> p;
        if (in)
            m.paise = r * 100 + p;
        return in;
    }
};

int main() {
    Money a(120, 75), b(79, 25);

    Money c = a + b;

    cout << c << '\n';
    cout << boolalpha << (c == Money(200)) << '\n';

    // Paise carry test
    Money x(0, 75), y(0, 50);
    cout << x + y << '\n';

    // Subtraction test
    cout << Money(10) - Money(15) << '\n';

    // += test
    a += b;
    cout << a << '\n';

    // Less-than test
    cout << (Money(50) < Money(100)) << '\n';

    return 0;
}
