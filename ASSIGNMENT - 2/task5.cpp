
    void print() const {
        cout << name << ": "
             << (seat ? "Seat " + to_string(seat) :
                 "Waiting")
             << endl;
    }
};

int BusTicket::issued = 0;

int main() {
    BusTicket trip[4] = {
        BusTicket("Asha"),
        BusTicket("Bala"),
        BusTicket("Chitra"),
        BusTicket("Dev")
    };

    for (const BusTicket& t : trip)
        t.print();

    cout << "Issued: " << BusTicket::count() << endl;

    return 0;
}
