
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b) {
    int t1 = a.h * 60 + a.m;
    int t2 = b.h * 60 + b.m;

    return (t1 > t2) ? t1 - t2 : t2 - t1;
}

bool earlier(const Time& a, const Time& b) {
    int t1 = a.h * 60 + a.m;
    int t2 = b.h * 60 + b.m;

    return t1 < t2;
}

int main() {
    Time departure(9, 45), arrival(13, 10);

    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';

    return 0;
}
