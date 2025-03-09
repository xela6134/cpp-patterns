#include <iostream>
#include <string>

/**
 * Parent Class (Transport)
 */
class Transport {
 public:
    virtual ~Transport() = default;
    virtual void deliver() const = 0;
};

/**
 * Subclass (Truck)
 */
class Truck : public Transport {
 public:
    Truck() {
        this->method = "Delivering on a truck on land!";
    }

    void deliver() const override {
        std::cout << method << std::endl;
    }
 private:
    std::string method;
};

/**
 * Subclass (Ship)
 */
class Ship : public Transport {
 public:
    Ship() {
        this->method = "Delivering on a ship on water!";
    }

    void deliver() const override {
        std::cout << method << std::endl;
    }
 private:
    std::string method;
};


// Awful Code Without Factory
int main() {
    std::string transportType;
    std::cout << "Enter transport type (truck/ship): ";
    std::cin >> transportType;

    Transport* transport;
    if (transportType == "truck") {
        transport = new Truck();
    } else if (transportType == "ship") {
        transport = new Ship();
    } else {
        std::cout << "Invalid transport type!" << std::endl;
        return 1;
    }

    // Direct function call instead of polymorphism
    transport->deliver();

    // Manual memory management (Not using smart pointers)
    delete transport;

    // Duplicated object creation
    Transport* transport2;
    if (transportType == "truck") {
        transport2 = new Truck();
    } else if (transportType == "ship") {
        transport2 = new Ship();
    } else {
        std::cout << "Invalid transport type!" << std::endl;
        return 1;
    }

    transport2->deliver();
    delete transport2;

    return 0;
}
