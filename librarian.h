#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>

class Librarian {
public:
    Librarian();
    void enterDetails();
    void displayDetails() const;
private:
    int staffId;
    std::string name;
    std::string address;
    std::string email;
    int salary;

    bool isValidStaffId(int id) const;
    bool isValidEmail(const std::string& email) const;
    bool isValidSalary(int salary) const;
};

#endif // LIBRARIAN_H
