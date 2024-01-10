#include <iostream>
#include <fstream>  
#include <cstdlib>
#include <limits> 
#include "Librarian.h"
#include "Member.h"
#include "book.h"

void showMenu() {
    std::cout << "\nWelcome to the Library System\n";
    std::cout << "----------------------------------\n";
    std::cout << "1. Add Member\n";
    std::cout << "2. Issue Book\n";
    std::cout << "3. Return Book\n";
    std::cout << "4. Display Borrowed Books\n";
    std::cout << "5. Calculate Fine\n";
    std::cout << "6. Exit\n";
    std::cout << "----------------------------------\n";
    std::cout << "Enter your choice: ";
}
int main() {
    int startupChoice;
    std::cout << "1. New User\n";
    std::cout << "2. Login\n";
    std::cout << "Enter your choice: ";
    std::cin >> startupChoice;

    if (startupChoice == 1) {
        // New User Registration
        Librarian librarian;
        librarian.enterDetails();
    
    } else if (startupChoice == 2) {
        // Login Process (not implemented yet)
        std::cout << "Login feature coming soon.\n";
    } else {
        std::cout << "Invalid choice.\n";
        return 0;
    }


    // Clear the screen
    system("clear"); 
    int memberId;
    int choice;
    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {



            case 1:
                 {
        Member member;
        member.enterDetails();
        member.saveToFile();
        Member::displayAllMembers();
    }
                break;

          
case 2: // Option for issuing a book

    std::cout << "Enter Member ID: ";
    std::cin >> memberId;
    if (Member::doesMemberExist(memberId)) {
        std::cout << "ID matched successfully. Available Books:\n";
        Book::displayBookTypes();

        std::string selectedType;
        std::cout << "Enter the type of book you want: ";
        std::cin.ignore(); // To clear the newline character left in the stream
        std::getline(std::cin, selectedType);
        Book::displayBooksByType(selectedType);

        int bookId;
        std::cout << "Enter the ID of the book to borrow: ";
        std::cin >> bookId;
        if (!Book::borrowBookById(bookId, memberId)) {
            std::cout << "Unable to borrow the book. Please try again.\n";
        }
    } else {
        std::cout << "Error: Enter valid ID or get ID from 'Add Member'.\n";
    }
    break;




    case 3: { // Option for returning a book
        std::cout << "Enter Member ID: ";
        std::cin >> memberId;
        if (Member::doesMemberExist(memberId)) {
            std::cout << "ID matched successfully.\n";
            Book::displayBorrowedBooksByMemberId(memberId);

          int bookId;
    std::cout << "Enter the ID of the book to return: ";
    std::cin >> bookId;
    if (Book::returnBookById(bookId, memberId)) {
        std::cout << "Book ID " << bookId << " returned successfully.\n";
    } else {
        std::cout << "Unable to find a record for Book ID " << bookId << " for Member ID " << memberId << ".\n";
    }
    break;
    }
    }
            case 4:
 Book::displayAllBorrowedBooks();

                break;
       
case 5:
    std::cout << "Enter Member ID: ";
    std::cin >> memberId;
    Book::calculateFine(memberId);
    break;


            case 6:
                std::cout << "Exiting the Library System. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
