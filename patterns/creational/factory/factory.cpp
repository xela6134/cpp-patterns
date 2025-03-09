#include <iostream>
#include <memory>
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

/**
 * Factory Pattern which creates new instances of Transportations
 */
class TransportFactory {
public:
    // Static factory method that creates transports
    static std::unique_ptr<Transport> createTransport(const std::string& type) {
        if (type == "truck") {
            return std::make_unique<Truck>();
        } else if (type == "ship") {
            return std::make_unique<Ship>();
        } else {
            throw std::invalid_argument("Unknown transport type");
        }
    }
};

int main() {
    auto truck = TransportFactory::createTransport("truck");
    truck->deliver();

    auto ship = TransportFactory::createTransport("ship");
    ship->deliver();

    try {
        auto plane = TransportFactory::createTransport("plane");
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}
