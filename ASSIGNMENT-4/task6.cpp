
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Abstract base class
class Vehicle {
protected:
    string registrationNumber;
    double dailyRate;
    bool rented;

public:
    Vehicle(string reg, double rate)
        : registrationNumber(reg), dailyRate(rate), rented(false) {}

    virtual double calculateCharge(int days) const = 0;

    virtual void display() const {
        cout << "Registration: " << registrationNumber
             << ", Daily Rate: " << dailyRate;
    }

    void rent() {
        if (!rented) {
            rented = true;
            cout << registrationNumber << " rented successfully\n";
        } else {
            cout << registrationNumber << " is already rented\n";
        }
    }

    void returnVehicle(int days, int lateDays) {
        if (rented) {
            double rental = calculateCharge(days);
            double lateFee = lateDays * dailyRate * 0.5;

            cout << registrationNumber
                 << " rental charge: " << rental
                 << ", late fee: " << lateFee
                 << ", total: " << rental + lateFee << '\n';

            rented = false;
        } else {
            cout << registrationNumber
                 << " was not rented\n";
        }
    }

    virtual ~Vehicle() = default;
};

// Bicycle class
class Bicycle : public Vehicle {
public:
    Bicycle(string reg, double rate)
        : Vehicle(reg, rate) {}

    double calculateCharge(int days) const override {
        return dailyRate * days;
    }

    void display() const override {
        cout << "Bicycle - ";
        Vehicle::display();
        cout << '\n';
    }
};

// Intermediate class for motor vehicles
class MotorVehicle : public Vehicle {
protected:
    double energyLevel;
    string serviceDueDate;

public:
    MotorVehicle(string reg, double rate,
                 double energy, string date)
        : Vehicle(reg, rate),
          energyLevel(energy),
          serviceDueDate(date) {}

    void displayMotorDetails() const {
        cout << ", Fuel/Charge Level: " << energyLevel
             << "%, Service Due: " << serviceDueDate;
    }
};

// TwoWheeler class
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string reg, double rate,
               double fuel, string date)
        : MotorVehicle(reg, rate, fuel, date) {}

    double calculateCharge(int days) const override {
        return dailyRate * days;
    }

    void display() const override {
        cout << "TwoWheeler - ";
        Vehicle::display();
        displayMotorDetails();
        cout << '\n';
    }
};

// Car class
class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(string reg, double rate, double fuel,
        string date, int seats)
        : MotorVehicle(reg, rate, fuel, date),
          seatingCapacity(seats) {}

    double calculateCharge(int days) const override {
        return dailyRate * days;
    }

    void display() const override {
        cout << "Car - ";
        Vehicle::display();
        displayMotorDetails();
        cout << ", Seats: " << seatingCapacity << '\n';
    }
};

// ElectricCar class
class ElectricCar : public Car {
private:
    double batteryCapacity;
    double costPerKWh;

public:
    ElectricCar(string reg, double rate, double charge,
                string date, int seats,
                double battery, double cost)
        : Car(reg, rate, charge, date, seats),
          batteryCapacity(battery),
          costPerKWh(cost) {}

    double calculateCharge(int days) const override {
        double chargingCost = batteryCapacity * costPerKWh;
        return (dailyRate * days) + chargingCost;
    }

    void display() const override {
        cout << "ElectricCar - ";
        Vehicle::display();
        displayMotorDetails();
        cout << ", Seats: " << seatingCapacity
             << ", Battery: " << batteryCapacity
             << " kWh\n";
    }
};

// New type added without modifying existing classes
class ElectricBus : public Vehicle {
private:
    double batteryCapacity;
    double costPerKWh;
    string serviceDueDate;

public:
    ElectricBus(string reg, double rate,
                double battery, double cost,
                string date)
        : Vehicle(reg, rate),
          batteryCapacity(battery),
          costPerKWh(cost),
          serviceDueDate(date) {}

    double calculateCharge(int days) const override {
        return dailyRate * days
             + batteryCapacity * costPerKWh;
    }

    void display() const override {
        cout << "ElectricBus - ";
        Vehicle::display();
        cout << ", Battery: " << batteryCapacity
             << " kWh, Service Due: "
             << serviceDueDate << '\n';
    }
};

int main() {
    cout << fixed << setprecision(2);

    Bicycle bicycle("BIKE101", 100);
    TwoWheeler bike("TW201", 200, 80, "2026-12-01");
    Car car("CAR301", 1000, 70, "2026-12-10", 5);
    ElectricCar ecar("EV401", 1200, 90,
                     "2026-12-15", 5, 50, 8);
    ElectricBus bus("BUS501", 2000, 100, 7,
                    "2026-12-20");

    // Array of base-class pointers
    Vehicle* fleet[] = {
        &bicycle, &bike, &car, &ecar, &bus
    };

    int count = 5;

    cout << "VEHICLE FLEET\n";

    for (int i = 0; i < count; i++) {
        fleet[i]->display();
    }

    cout << "\nRENTING VEHICLES\n";

    for (int i = 0; i < count; i++) {
        fleet[i]->rent();
    }

    cout << "\nRETURNING VEHICLES\n";

    for (int i = 0; i < count; i++) {
        int lateDays = (i == 2) ? 1 : 0;
        fleet[i]->returnVehicle(2, lateDays);
    }

    return 0;
}
