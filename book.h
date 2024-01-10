#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <set>

class Book {
public:
    static void displayBookTypes();
    static void displayBooksByType(const std::string& type);
    static bool borrowBookById(int bookId, int memberId);  
     static void displayBorrowedBooksByMemberId(int memberId);
   static void displayAllBorrowedBooks(); 
static bool returnBookById(int bookId, int memberId);
   static void calculateFine(int memberId);

private:
    static std::vector<std::string> readBooksFromFile();
    static std::set<std::string> extractBookTypes(const std::vector<std::string>& books);

    // ... Rest of the class ...
};

#endif // BOOK_H
