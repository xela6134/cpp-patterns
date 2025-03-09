#include <iostream>
#include <memory>
#include <string>

/**
 * Final product: House (with many different features)
 */
class House {
 public:
    void buildWalls(const std::string& walls) {
        this->walls = walls;
    }

    void buildDoors(const std::string& doors) {
        this->doors = doors;
    }

    void buildWindows(const std::string& windows) {
        this->windows = windows;
    }

    void buildRoof(const std::string& roof) {
        this->roof = roof;
    }

    void buildGarage(const std::string& garage) {
        this->garage = garage;
    }

    std::string getResult() const {
        return "This house has " 
            + walls + " walls, "
            + doors + " doors, "
            + windows + " windows, "
            + roof + " roof, and "
            + garage + " garage.\n";
    }

 private:
    std::string walls, doors, windows, roof, garage;
};

/**
 * Abstract Builder
 * (Base Class)
 */
class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    virtual void buildWalls() = 0;
    virtual void buildDoors() = 0;
    virtual void buildWindows() = 0;
    virtual void buildRoof() = 0;
    virtual void buildGarage() = 0;
    virtual std::shared_ptr<House> getResult() = 0;
};

/**
 * Wooden House Builder
 * (Derived Class)
 */
class WoodenHouseBuilder : public HouseBuilder {
 public:
    WoodenHouseBuilder() { 
        house = std::make_shared<House>(); 
    }

    void buildWalls() override { 
        house->buildWalls("Wooden"); 
    }
    
    void buildDoors() override { 
        house->buildDoors("Wooden"); 
    }

    void buildWindows() override { 
        house->buildWindows("Glass"); 
    }

    void buildRoof() override { 
        house->buildRoof("Metal"); 
    }

    void buildGarage() override { 
        house->buildGarage("Cobblestone"); 
    }

    std::shared_ptr<House> getResult() override { 
        return house;
    }
 private:
    std::shared_ptr<House> house;
};

/**
 * Fancy House Builder
 * (Derived Class)
 */
class FancyHouseBuilder : public HouseBuilder {
 public:
    FancyHouseBuilder() { 
        house = std::make_shared<House>(); 
    }

    void buildWalls() override { 
        house->buildWalls("Golden"); 
    }
    
    void buildDoors() override { 
        house->buildDoors("Platinum"); 
    }

    void buildWindows() override { 
        house->buildWindows("Diamond"); 
    }

    void buildRoof() override { 
        house->buildRoof("Ruby"); 
    }

    void buildGarage() override { 
        house->buildGarage("Emerald"); 
    }

    std::shared_ptr<House> getResult() override { 
        return house;
    }
 private:
    std::shared_ptr<House> house;
};

/**
 * House Building Director
 * (Directs the building process)
 */
class UniqueHouseDirector {
 public:
    void setBuilder(std::unique_ptr<HouseBuilder> newBuilder) { 
        builder = std::move(newBuilder);    // Transferring unique ownership
    }

    // Just because we have UniqueHouseDirector doesn't mean the House can be unique as well
    // A UniqueHouseDirector has its unique 'Builder' not its 'House'
    std::shared_ptr<House> construct() {
        if (not builder) {
            throw std::runtime_error("Builder not set (unique_ptr)!");
        }

        builder->buildWalls();
        builder->buildDoors();
        builder->buildWindows();
        builder->buildRoof();
        builder->buildGarage();
        return builder->getResult();
    }
 private:
    // Unique ownership of a builder
    std::unique_ptr<HouseBuilder> builder;
};

class SharedHouseDirector {
public:
    void setBuilder(std::shared_ptr<HouseBuilder> newBuilder) {
        builder = newBuilder;               // Shared ownership
    }

    std::shared_ptr<House> construct() {
        if (!builder) {
            throw std::runtime_error("Builder not set (shared_ptr)!");
        }
        builder->buildWalls();
        builder->buildDoors();
        builder->buildWindows();
        builder->buildRoof();
        builder->buildGarage();
        return builder->getResult();
    }

private:
    // Shared ownership of the builder
    std::shared_ptr<HouseBuilder> builder;
};


int main() {
    // Demo 1: UniquePtr Director
    {
        UniqueHouseDirector directorUnique;

        // This creates a unique_ptr<FancyHouseBuilder>
        auto uniqueBuilder = std::make_unique<FancyHouseBuilder>();

        // Moving ownership into director1
        directorUnique.setBuilder(std::move(uniqueBuilder));

        // Now uniqueBuilder is nullptr; not reusable
        auto house1 = directorUnique.construct();

        std::cout << "House1 => " << house1->getResult();
    }

    // Demo 2: SharedPtr Director
    {
        // Create TWO directors that share the same builder
        SharedHouseDirector directorA, directorB;

        // One shared builder
        auto sharedBuilder = std::make_shared<WoodenHouseBuilder>();

        directorA.setBuilder(sharedBuilder);
        directorB.setBuilder(sharedBuilder);

        // Both directors will call construct on the SAME builder
        auto houseA = directorA.construct();
        auto houseB = directorB.construct();

        std::cout << "HouseA => " << houseA->getResult();
        std::cout << "HouseB => " << houseB->getResult();
    }

    return 0;
}
