#include <iostream>
#include <string>

// A simple House class with a LOT of setters
class House {
public:
    void setWalls(const std::string& walls) { 
        this->walls = walls; 
    }
    
    void setDoors(const std::string& doors) { 
        this->doors = doors; 
    }

    void setWindows(const std::string& windows) { 
        this->windows = windows; 
    }

    void setRoof(const std::string& roof) { 
        this->roof = roof; 
    }

    void setGarage(const std::string& garage) { 
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

int main() {
    // Bad approach: manually configuring a House
    House myHouse;

    // Messy if/else logic scattered all over main
    bool useWood = true;
    if (useWood) {
        myHouse.setWalls("Wooden");
        myHouse.setDoors("Wooden");
    } else {
        myHouse.setWalls("Concrete");
        myHouse.setDoors("Steel");
    }
    
    // More direct calls to set properties
    int windowQuality = 1;
    if (windowQuality == 1) {
        myHouse.setWindows("Glass");
    } else if (windowQuality == 2) {
        myHouse.setWindows("Reinforced Glass");
    } else {
        myHouse.setWindows("Plastic");
    }
    
    // Even more direct calls
    myHouse.setRoof("Shingle");
    myHouse.setGarage("Detached");

    // Finally printing the result after a million direct calls
    std::cout << myHouse.getResult() << std::endl;

    return 0;
}