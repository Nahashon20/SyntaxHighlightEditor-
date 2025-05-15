#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your age: ";
    std::cin >> age;

    int year = 2025 + (100 - age);
    std::cout << "Hello, " << name << "! You will turn 100 in the year " << year << "." << std::endl;

    return 0;
}
