#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    int id;
    string address;

public:
    Person(const string& name, int id, const string& address) : name(name), id(id), address(address) {}
    virtual ~Person() {}

    virtual void displayInfo() const = 0; 
    virtual double calculatePayment() const = 0; 
};

class Student : public Person {
private:
    int semester;

public:
    Student(const string& name, int id, const string& address, int semester) : Person(name, id, address), semester(semester) {}

    void displayInfo() const override {
        cout << "Student: " << name << ", ID: " << id << ", Address: " << address << ", Semester: " << semester << endl;
    }

    double calculatePayment() const override {
        return 1000.0 * semester; 
    }
};

class Employee : public Person {
protected:
    double monthlySalary;

public:
    Employee(const string& name, int id, const string& address, double monthlySalary) : Person(name, id, address), monthlySalary(monthlySalary) {}

    double calculatePayment() const override {
        return monthlySalary; 
    }
};

class Teacher : public Employee {
private:
    string department;

public:
    Teacher(const string& name, int id, const string& address, double monthlySalary, const string& department)
        : Employee(name, id, address, monthlySalary), department(department) {}

    void displayInfo() const override {
        cout << "Teacher: " << name << ", ID: " << id << ", Address: " << address << ", Department: " << department << endl;
    }
};

class Staff : public Employee {
private:
    string position;

public:
    Staff(const string& name, int id, const string& address, double monthlySalary, const string& position)
        : Employee(name, id, address, monthlySalary), position(position) {}

    void displayInfo() const override {
        cout << "Staff: " << name << ", ID: " << id << ", Address: " << address << ", Position: " << position << endl;
    }
};

class Route {
private:
    string routeName;
    string startPoint;
    string endPoint;

public:
    Route(const string& routeName, const string& startPoint, const string& endPoint)
        : routeName(routeName), startPoint(startPoint), endPoint(endPoint) {}

    void displayRouteInfo() const {
        cout << "Route: " << routeName << ", Start: " << startPoint << ", End: " << endPoint << endl;
    }

    bool operator==(const Route& other) const {
        return (routeName == other.routeName && startPoint == other.startPoint && endPoint == other.endPoint);
    }
};

class Vehicle {
private:
    string vehicleNumber;
    Route* route;

public:
    Vehicle(const string& vehicleNumber, Route* route) : vehicleNumber(vehicleNumber), route(route) {}

    void displayVehicleInfo() const {
        cout << "Vehicle: " << vehicleNumber << endl;
        route->displayRouteInfo();
    }
};

class TransportationSystem {
private:
    Person* people[100];
    int personCount;
    Route* routes[10];
    int routeCount;

public:
    TransportationSystem() : personCount(0), routeCount(0) {}

    void addPerson(Person* person) {
        if (personCount < 100) {
            people[personCount++] = person;
        } else {
            cout << "Max persons reached!" << endl;
        }
    }

    void addRoute(Route* route) {
        if (routeCount < 10) {
            routes[routeCount++] = route;
        } else {
            cout << "Max routes reached!" << endl;
        }
    }

    void displayAllPeople() const {
        for (int i = 0; i < personCount; ++i) {
            people[i]->displayInfo();
        }
    }

    void displayAllRoutes() const {
        for (int i = 0; i < routeCount; ++i) {
            routes[i]->displayRouteInfo();
        }
    }
};

int main() {

    Route route1("R1", "Campus A", "Campus B");
    Route route2("R2", "Campus C", "Campus D");

    Student student1("Alice", 101, "Address 1", 2);
    Teacher teacher1("Dr. Smith", 201, "Address 2", 5000.0, "CS");
    Staff staff1("Bob", 301, "Address 3", 3000.0, "Admin");

    Vehicle vehicle1("V1", &route1);
    Vehicle vehicle2("V2", &route2);

    TransportationSystem system;
    system.addRoute(&route1);
    system.addRoute(&route2);
    system.addPerson(&student1);
    system.addPerson(&teacher1);
    system.addPerson(&staff1);

    system.displayAllPeople();
    system.displayAllRoutes();

    vehicle1.displayVehicleInfo();
    vehicle2.displayVehicleInfo();

    cout << "Route 1 == Route 2: " << (route1 == route2) << endl; 

    return 0;
}