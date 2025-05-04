#include "solution.h"
#include <iostream>
#include <sstream>

int main() {
    DogWalkingManager manager;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == ".") break;

        std::istringstream iss(line);
        std::string first;
        iss >> first;

        if (first.length() == 1) {
            char lastInitial;
            int strength;
            iss >> lastInitial >> strength;
            manager.addEmployee(first[0], lastInitial, strength);
        } else {
            int power;
            iss >> power;
            manager.addDog(first, power);
        }
    }

    manager.process();
    manager.printResults();

    return 0;
}
