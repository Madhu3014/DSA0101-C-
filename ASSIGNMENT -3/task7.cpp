#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Time {
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0) {
        seconds = h * 3600 + m * 60 + s;
    }

    // Prefix ++
    Time& operator++() {
        ++seconds;
        return *this;
    }

    // Postfix ++
    Time operator++(int) {
        Time old = *this;
        ++seconds;
        return old;
    }

    bool operator==(const Time& t) const {
        return seconds == t.seconds;
    }

    bool operator<(const Time& t) const {
        return seconds < t.seconds;
    }

    void display() const {
        int h = seconds / 3600;
        int m = (seconds % 3600) / 60;
        int s = seconds % 60;

        cout << h << ":";
        if (m < 10) cout << "0";
        cout << m << ":";
        if (s < 10) cout << "0";
        cout << s << endl;
    }
};

class Playlist {
    vector<string> tracks;

public:
    Playlist(vector<string> t) : tracks(t) {}

    string& operator[](int i) {
        if (i < 0 || i >= (int)tracks.size())
            throw out_of_range("Invalid playlist index");
        return tracks[i];
    }

    const string& operator[](int i) const {
        if (i < 0 || i >= (int)tracks.size())
            throw out_of_range("Invalid playlist index");
        return tracks[i];
    }

    int size() const {
        return tracks.size();
    }
};

int main() {
    Time t(0, 0, 5);

    Time a = t++;
    Time b = ++t;

    cout << "Postfix value: ";
    a.display();

    cout << "Prefix value: ";
    b.display();

    cout << "Current time: ";
    t.display();

    Time x(0, 0, 10), y(0, 0, 15);
    cout << boolalpha;
    cout << "x < y: " << (x < y) << endl;
    cout << "x == y: " << (x == y) << endl;

    Playlist p({"Song A", "Song B", "Song C"});

    cout << "\nPlaylist:\n";
    for (int i = 0; i < p.size(); i++)
        cout << p[i] << endl;

    cout << "\nPlayback:\n";
    cout << "Playing: " << p[0] << endl;
    cout << "Playing: " << p[1] << endl;

    try {
        cout << p[-1] << endl;
    }
    catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    try {
        cout << p[p.size()] << endl;
    }
    catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    Time rollover(0, 59, 59);
    ++rollover;
    cout << "\nAfter rollover: ";
    rollover.display();
}
ALTERNATIVE CONCEPT
#include <iostream>
using namespace std;

struct Counter {
    int v;

    Counter& operator++() {
        ++v;
        return *this;
    }

    Counter operator++(int) {
        Counter old = *this;
        ++v;
        return old;
    }
};

int main() {
    Counter c{5};
    Counter a = c++;
    Counter b = ++c;

    cout << a.v << ' ' << b.v << ' ' << c.v << '\n';
}
