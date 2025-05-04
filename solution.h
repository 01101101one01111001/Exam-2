#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <vector>
#include <climits>

class Dog {
private:
    std::string name;
    int power;
    bool matched;
public:
    Dog(const std::string& name, int power);
    std::string getName() const;
    int getPower() const;
    bool isMatched() const;
    void setMatched(bool matched);
};

class Employee {
private:
    char firstNameInitial;
    char lastNameInitial;
    int strength;
    bool hasWork;
public:
    Employee(char first, char last, int strength);
    char getFirstNameInitial() const;
    char getLastNameInitial() const;
    int getStrength() const;
    bool hasWorkAssigned() const;
    void assignWork(bool hasWork);
    std::string getInitials() const;
};

class DogWalkingManager {
public:
    void addDog(const std::string& name, int power);
    void addEmployee(char first, char last, int strength);
    void process();
    void printResults() const;

private:
    std::vector<Dog> dogs;
    std::vector<Employee> employees;
    std::vector<std::pair<const Dog*, const Employee*>> matches; // добавено това
    void matchDogsAndEmployees();
};
#endif // SOLUTION_H
