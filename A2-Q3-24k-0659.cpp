#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string vehicleID;
    static int activeDeliveries;
public:
    Vehicle(std::string id) : vehicleID(id) {
        activeDeliveries++;
    }
    virtual ~Vehicle() {
        activeDeliveries--;
    }
    virtual void calculateRoute() = 0;
    virtual int estimatedDeliveryTime() = 0;
    static int getActiveDeliveries() {
        return activeDeliveries;
    }
};

int Vehicle::activeDeliveries = 0;

class RamzanDrone : public Vehicle {
public:
    RamzanDrone(std::string id) : Vehicle(id) {}
    void calculateRoute() override {
        std::cout << "Calculating aerial route for drone " << vehicleID << std::endl;
    }
    int estimatedDeliveryTime() override {
        return 30; // in minutes
    }
};

class RamzanTimeShip : public Vehicle {
public:
    RamzanTimeShip(std::string id) : Vehicle(id) {}
    void calculateRoute() override {
        std::cout << "Verifying historical consistency for time ship " << vehicleID << std::endl;
    }
    int estimatedDeliveryTime() override {
        return 60; // in minutes
    }
};

class RamzanHyperPod : public Vehicle {
public:
    RamzanHyperPod(std::string id) : Vehicle(id) {}
    void calculateRoute() override {
        std::cout << "Navigating underground tunnel for hyper pod " << vehicleID << std::endl;
    }
    int estimatedDeliveryTime() override {
        return 45; // in minutes
    }
};

void command(std::string action, std::string packageID) {
    std::cout << action << " command issued for package " << packageID << std::endl;
}

void command(std::string action, std::string packageID, std::string urgencyLevel) {
    std::cout << action << " command issued for package " << packageID << " with urgency level " << urgencyLevel << std::endl;
}

int main() {
    RamzanDrone drone("D001");
    RamzanTimeShip timeShip("T001");
    RamzanHyperPod hyperPod("H001");

    drone.calculateRoute();
    timeShip.calculateRoute();
    hyperPod.calculateRoute();

    command("Deliver", "P001");
    command("Deliver", "P002", "Urgent");

    std::cout << "Active Deliveries: " << Vehicle::getActiveDeliveries() << std::endl;

    return 0;
}