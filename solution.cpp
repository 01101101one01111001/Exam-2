#include "solution.h"
#include <iostream>
#include <algorithm>
#include <climits>

Dog::Dog(const std::string& name, int power) : name(name), power(power), matched(false) {}

std::string Dog::getName() const { return name; }
int Dog::getPower() const { return power; }
bool Dog::isMatched() const { return matched; }
void Dog::setMatched(bool matched) { this->matched = matched; }

Employee::Employee(char first, char last, int strength) :
    firstNameInitial(first), lastNameInitial(last), strength(strength), hasWork(false) {}

char Employee::getFirstNameInitial() const { return firstNameInitial; }
char Employee::getLastNameInitial() const { return lastNameInitial; }
int Employee::getStrength() const { return strength; }
bool Employee::hasWorkAssigned() const { return hasWork; }
void Employee::assignWork(bool hasWork) { this->hasWork = hasWork; }
std::string Employee::getInitials() const { return std::string() + firstNameInitial + lastNameInitial; }

void DogWalkingManager::addDog(const std::string& name, int power) { dogs.emplace_back(name, power); }
void DogWalkingManager::addEmployee(char first, char last, int strength) { employees.emplace_back(first, last, strength); }

void DogWalkingManager::matchDogsAndEmployees() {
    for (auto& dog : dogs) dog.setMatched(false);
    for (auto& emp : employees) emp.assignWork(false);
    matches.clear();


    std::vector<Dog*> sortedDogs;
    for (auto& d : dogs) sortedDogs.push_back(&d);
    std::sort(sortedDogs.begin(), sortedDogs.end(),
              [](Dog* a, Dog* b) { return a->getPower() > b->getPower(); });


    std::vector<Employee*> sortedEmployees;
    for (auto& e : employees) sortedEmployees.push_back(&e);
    std::sort(sortedEmployees.begin(), sortedEmployees.end(),
              [](Employee* a, Employee* b) { return a->getStrength() < b->getStrength(); });

    for (Dog* dog : sortedDogs) {
        Employee* best = nullptr;
        int minDiff = INT_MAX;

        for (Employee* emp : sortedEmployees) {
            if (emp->hasWorkAssigned()) continue;
            int diff = emp->getStrength() - dog->getPower();
            if (diff >= 0 && diff < minDiff) {
                minDiff = diff;
                best = emp;
            }
        }

        if (best) {
            dog->setMatched(true);
            best->assignWork(true);
            matches.emplace_back(dog, best);
        }
    }
}

void DogWalkingManager::printResults() const {
    if (dogs.empty() && employees.empty()) {
        std::cout << "Matched: none.\nDogs without a walker: none.\nEmployees without work: none.\n";
        return;
    }

    std::cout << "Matched:\n";
    if (matches.empty()) {
        std::cout << "- none.\n";
    } else {
        for (const Dog& dog : dogs) {
            auto it = std::find_if(matches.begin(), matches.end(),
                                   [&](const auto& pair) { return pair.first == &dog; });
            if (it != matches.end()) {
                const Employee* emp = it->second;
                std::cout << "- Dog " << dog.getName() << ":" << dog.getPower()
                          << " with " << emp->getInitials() << ":" << emp->getStrength() << ".\n";
            }
        }
    }

    std::cout << "Dogs without a walker:";
    bool any = false;
    for (const auto& dog : dogs) {
        if (!dog.isMatched()) {
            if (!any) std::cout << "\n";
            std::cout << "- " << dog.getName() << ":" << dog.getPower() << "\n";
            any = true;
        }
    }
    if (!any) std::cout << " none.\n";

    std::cout << "Employees without work:";
    any = false;
    for (const auto& emp : employees) {
        if (!emp.hasWorkAssigned()) {
            if (!any) std::cout << "\n";
            std::cout << "- " << emp.getInitials() << ":" << emp.getStrength() << "\n";
            any = true;
        }
    }
    if (!any) std::cout << " none.\n";
}

void DogWalkingManager::process() {
    matchDogsAndEmployees();
}
