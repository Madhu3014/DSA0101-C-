
#include <iostream>
using namespace std;

int& highestMark(int marks[], int n) {
    int maxIndex = 0;

    for (int i = 1; i < n; i++) {
        if (marks[i] > marks[maxIndex])
            maxIndex = i;
    }

    return marks[maxIndex];
}

int main() {
    int marks[] = {75, 90, 85, 95, 80};

    cout << "Highest mark: " << highestMark(marks, 5) <<
    endl;

    highestMark(marks, 5) += 2;

    cout << "After moderation: " << highestMark(marks, 5) <<
    endl;

    return 0;
}
