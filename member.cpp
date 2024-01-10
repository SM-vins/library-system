#include "Member.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
const std::string FILE_NAME = "members.txt";

Member::Member() : memberId(0) {}
bool Member::doesMemberExist(int memberId) {
    std::ifstream inFile(FILE_NAME);
    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string id;
        getline(iss, id, ',');
        if (std::to_string(memberId) == id) {
            return true;
        }
    }
    return false;
}

bool Member::isMemberExists() const {
    std::ifstream inFile(FILE_NAME);
    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string id, existingName, existingAddress, existingEmail;
        getline(iss, id, ',');
        getline(iss, existingName, ',');
        getline(iss, existingAddress, ',');
        getline(iss, existingEmail, ',');

        if (std::to_string(memberId) == id || name == existingName || email == existingEmail) {
            return true;
        }
    }
    return false;
}

void Member::enterDetails() {
    bool detailsExist;
    do {
        std::cout << "Enter member details:\n";

        // Member ID
        std::cout << "Member ID (positive integer): ";
        std::cin >> memberId;
        while (!isValidMemberId(memberId)) {
            std::cout << "Error: Please enter a valid, positive integer for the member ID.\n";
            std::cin >> memberId;
        }

        // Name
        std::cout << "Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        // Address
        std::cout << "Address: ";
        std::getline(std::cin, address);

        // Email
        std::cout << "Email (in email format): ";
        std::getline(std::cin, email);
        while (!isValidEmail(email)) {
            std::cout << "Error: Please enter a valid email address.\n";
            std::getline(std::cin, email);
        }

        detailsExist = isMemberExists();
        if (detailsExist) {
            std::cout << "Error: Member with these details already exists. Please enter different details.\n";
        }
    } while (detailsExist);

    std::cout << "Member added successfully.\n";
}
void Member::saveToFile() const {
    std::ofstream outFile(FILE_NAME, std::ios::app);
    outFile << memberId << ", " << name << ", " << address << ", " << email << "\n";
    outFile.close();
}

void Member::displayAllMembers() {
    std::ifstream inFile(FILE_NAME);
    std::string line;
    std::cout << "\nAll Members:\n";
    std::cout << "ID, Name, Address, Email\n";
    while (getline(inFile, line)) {
        std::cout << line << "\n";
    }
    inFile.close();
}

bool Member::isValidMemberId(int id) const {
    return id > 0;
}

bool Member::isValidEmail(const std::string& email) const {
    const std::regex emailPattern(R"(^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$)");
    return std::regex_match(email, emailPattern);
}
