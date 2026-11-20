
#include <iostream>
#include <climits>
using namespace std;

int main() {
    cout << "DATA TYPE SIZES" << endl;
    cout << "bool: " << sizeof(bool) << " bytes" << endl;
    cout << "char: " << sizeof(char) << " bytes" << endl;
    cout << "int: " << sizeof(int) << " bytes" << endl;
    cout << "long long: " << sizeof(long long) << " bytes" << endl;
    cout << "float: " << sizeof(float) << " bytes" << endl;
    cout << "double: " << sizeof(double) << " bytes" << endl;

    cout << "\nINTEGER LIMITS" << endl;
    cout << "INT_MIN: " << INT_MIN << endl;
    cout << "INT_MAX: " << INT_MAX << endl;
    cout << "UINT_MAX: " << UINT_MAX << endl;

    cout << "\nTYPE COMPATIBILITY" << endl;
    cout << "7 / 2 = " << 7 / 2 << endl;
    cout << "7.0 / 2 = " << 7.0 / 2 << endl;

    int value = 5;
    bool flag = value;
    cout << "Integer 5 converted to bool: "
         << boolalpha << flag << endl;

    cout << "\nNETWORK COLLECTION" << endl;
    long long totalPaise = 3000000LL * 3000;
    cout << "Total paise: " << totalPaise << endl;
    cout << "Total rupees: " << totalPaise / 100 << endl;

    return 0;
}
