#include "Librarian.h"
#include <iostream>
#include <regex>
#include <limits>
#include <fstream>
Librarian::Librarian() : staffId(0), salary(0) {}

void Librarian::enterDetails() {
    std::cout << "Enter details of the librarian:\n";

    // Staff ID
    do {
        std::cout << "Staff ID (positive integer): ";
        if(!(std::cin >> staffId) || !isValidStaffId(staffId)) {
            std::cout << "Error: Please enter a valid, positive integer for the staff ID.\n";
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input
        }
    } while (!isValidStaffId(staffId));

    // Name
    std::cout << "Name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    // Address
    std::cout << "Address: ";
    std::getline(std::cin, address);

    // Email
    do {
        std::cout << "Email (in email format): ";
        if(!(std::getline(std::cin, email)) || !isValidEmail(email)) {
            std::cout << "Error: Please enter a valid email address.\n";
        }
    } while (!isValidEmail(email));

    // Salary
    do {
        std::cout << "Salary (positive integer): ";
        if(!(std::cin >> salary) || !isValidSalary(salary)) {
            std::cout << "Error: Please enter a valid, positive integer for the salary.\n";
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input
        }
    } while (!isValidSalary(salary));
}

void Librarian::displayDetails() const {
    std::cout << "\nLibrarian Details:\n";
    std::cout << "Staff ID: " << staffId << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Address: " << address << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Salary: " << salary << "\n";
}

bool Librarian::isValidStaffId(int id) const {
    return id > 0;
}

bool Librarian::isValidEmail(const std::string& email) const {
    const std::regex emailPattern(R"(^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$)");
    return std::regex_match(email, emailPattern);
}

bool Librarian::isValidSalary(int salary) const {
    return salary > 0;
}
const std::string Librarian::fixedName = "abc";
const std::string Librarian::fixedAddress = "london";
const std::string Librarian::fixedEmail = "abc@gmail.com";

bool Librarian::doDetailsMatch() const {
    return staffId == fixedStaffId && name == fixedName && address == fixedAddress && email == fixedEmail && salary == fixedSalary;
}