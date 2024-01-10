#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>

class Librarian {
public:
    Librarian();
    void enterDetails();
    void displayDetails() const;
    bool doDetailsMatch() const;
private:
    int staffId;
    std::string name;
    std::string address;
    std::string email;
    int salary;

    bool isValidStaffId(int id) const;
    bool isValidEmail(const std::string& email) const;
    bool isValidSalary(int salary) const;
       static const int fixedStaffId = 123;  // Set fixed staff ID
    static const std::string fixedName;   // Fixed Name
    static const std::string fixedAddress; // Fixed Address
    static const std::string fixedEmail;   // Fixed Email
    static const int fixedSalary = 5000; 
};

#endif // LIBRARIAN_H
