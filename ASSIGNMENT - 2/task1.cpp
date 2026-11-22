
#include <iostream>
using namespace std;

// Call by value
void byValue(double fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside value: " << fee << endl;
}

// Call by reference
void byReference(double& fee, int percent) {
    fee -= fee * percent / 100;
}

// Call by pointer
void byPointer(double* fee, int percent) {
    *fee -= *fee * percent / 100;
}

int main() {
    double fee1 = 45000;
    double fee2 = 45000;
    double fee3 = 45000;

    byValue(fee1, 10);
    cout << "After value: " << fee1 << endl;

    byReference(fee2, 10);
    cout << "After reference: " << fee2 << endl;

    byPointer(&fee3, 10);
    cout << "After pointer: " << fee3 << endl;

    return 0;
}
