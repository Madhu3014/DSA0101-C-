
    cout << "\nBalance: Rs. " << fixed << setprecision(2)
         << balance;

    cout << "\nLast Transactions:\n";

    for (int i = 0; i < count; i++) {
        if (transactions[i] > 0)
            cout << "Deposit: Rs. " << transactions[i]
                 << endl;
        else
            cout << "Withdrawal: Rs. " << -transactions[i]
                 << endl;
    }
}

int main() {
    SavingsAccount s("ACC101", 5000);

    s.deposit(1000);
    s.withdraw(500);
    s.deposit(750);
    s.withdraw(250);

    s.miniStatement();

    return 0;
}
