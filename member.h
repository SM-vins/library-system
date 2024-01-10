#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
public:
    Member();
    void enterDetails();
    void saveToFile() const;
    static void displayAllMembers();
    static bool doesMemberExist(int memberId);

private:
    int memberId;
    std::string name;
    std::string address;
    std::string email;
     bool isMemberExists() const;
    bool isValidMemberId(int id) const;
    bool isValidEmail(const std::string& email) const;
};

#endif // MEMBER_H
