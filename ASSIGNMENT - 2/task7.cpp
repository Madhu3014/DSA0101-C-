
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// Original Shifting Array Method
class ShiftingArray {
    vector<int> data;
    int capacity;
    int count;

public:
    ShiftingArray(int size) {
        capacity = size;
        count = 0;
        data.resize(size);
    }

    void insert(int value) {
        if (count < capacity) {
            data[count++] = value;
        }
        else {
            for (int i = 1; i < capacity; i++) {
                data[i - 1] = data[i];
            }
            data[capacity - 1] = value;
        }
    }

    void display() const {
        for (int i = 0; i < count; i++)
            cout << data[i] << " ";
        cout << endl;
    }

    int last() const {
        return data[capacity - 1];
    }
};

// Redesigned Circular Buffer Method
class CircularBuffer {
    vector<int> data;
    int capacity;
    int count;
    int next;

public:
    CircularBuffer(int size) {
        capacity = size;
        count = 0;
        next = 0;
        data.resize(size);
    }

    void insert(int value) {
        data[next] = value;
        next = (next + 1) % capacity;

        if (count < capacity)
            count++;
    }

    void display() const {
        int start = (next - count + capacity) % capacity;

        for (int i = 0; i < count; i++) {
            cout << data[(start + i) % capacity] << " ";
        }
        cout << endl;
    }

    int last() const {
        return data[(next - 1 + capacity) % capacity];
    }
};

int main() {
    const int SIZE = 10;
    const int N = 1000000;

    // Display original shifting array
    ShiftingArray s1(SIZE);

    for (int i = 300; i <= 1200; i += 100)
        s1.insert(i);

    cout << "ORIGINAL SHIFTING ARRAY METHOD" << endl;
    s1.display();

    // Display redesigned circular buffer
    CircularBuffer c1(SIZE);

    for (int i = 300; i <= 1200; i += 100)
        c1.insert(i);

    cout << "\nREDESIGNED CIRCULAR BUFFER METHOD" << endl;
    c1.display();

    // Performance testing
    ShiftingArray s(SIZE);
    CircularBuffer c(SIZE);

    auto start = steady_clock::now();

    for (int i = 0; i < N; i++)
        s.insert(i);

    auto end = steady_clock::now();

    auto shiftTime =
        duration_cast<microseconds>(end - start).count();

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
        c.insert(i);

    end = steady_clock::now();

    auto circularTime =
        duration_cast<microseconds>(end - start).count();

    // Performance comparison
    cout << "\nPERFORMANCE COMPARISON\n";
    cout << "Number of insertions: " << N << endl;

    cout << "Shifting Array Time: "
         << shiftTime << " microseconds" << endl;

    cout << "Circular Buffer Time: "
         << circularTime << " microseconds" << endl;

    // Validation
    cout << "\nVALIDATION\n";

    cout << "Last value in original: "
         << s.last() << endl;

    cout << "Last value in redesigned: "
         << c.last() << endl;

    if (s.last() == c.last())
        cout << "Both methods produce the same final value.\n";
    else
        cout << "Validation failed.\n";

    return 0;
}
