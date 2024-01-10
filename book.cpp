#include "book.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <algorithm>

// ... other existing code ...

const std::string BOOKS_FILE = "books.csv";

std::vector<std::string> Book::readBooksFromFile() {
    std::vector<std::string> books;
    std::ifstream file(BOOKS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << BOOKS_FILE << std::endl;
        return books;
    }
    std::string line;
    while (getline(file, line)) {
        books.push_back(line);
    }
    return books;
}

std::set<std::string> Book::extractBookTypes(const std::vector<std::string>& books) {
    std::set<std::string> types;
    for (const auto& book : books) {
        std::istringstream iss(book);
        std::string segment;
        std::vector<std::string> seglist;

        while (getline(iss, segment, ',')) {
            seglist.push_back(segment);
        }
        if (seglist.size() > 4) { // Assuming type is the 5th element
            types.insert(seglist[4]); // Inserting type into set
        }
    }
    return types;
}

void Book::displayBookTypes() {
    auto books = readBooksFromFile();
    auto types = extractBookTypes(books);

    std::cout << "Available Book Types:\n";
    for (const auto& type : types) {
        std::cout << type << std::endl;
    }
}

void Book::displayBooksByType(const std::string& type) {
    auto books = readBooksFromFile();
    std::cout << "Books of type " << type << ":\n";

    for (const auto& book : books) {
        if (book.find(type) != std::string::npos) {
            std::cout << book << std::endl;
        }
    }
}


bool Book::borrowBookById(int bookId, int memberId) {
    std::vector<std::string> books = readBooksFromFile();
    bool bookFound = false;
    std::string bookIdStr, bookName, bookPageCount, bookAuthor, bookType;

    for (const auto& book : books) {
        std::istringstream iss(book);
        getline(iss, bookIdStr, ',');
        getline(iss, bookName, ',');
        getline(iss, bookPageCount, ',');
        getline(iss, bookAuthor, ',');
        getline(iss, bookType, ',');

        if (bookIdStr == std::to_string(bookId)) {
            bookFound = true;
            break; // Found the book, no need to continue
        }
    }

    if (bookFound) {
        // Get the current date as the issue date
        auto now = std::chrono::system_clock::now();
        std::time_t issueTime = std::chrono::system_clock::to_time_t(now);
        std::tm* issueDate = std::localtime(&issueTime);

        // Calculate the return date (3 days from now)
        std::tm returnDate = *issueDate;
        returnDate.tm_mday += 3; // Add 3 days
        mktime(&returnDate); // Normalize the date

        // Write borrowing details to the file with the new format
        std::ofstream outFile("borrow-book_details.txt", std::ios::app);
        if (outFile) {
            outFile << "Book ID: " << bookId 
                    << ",Name: " << bookName 
                    << ",Author: " << bookAuthor 
                    << ",Member ID: " << memberId 
                    << ",Issue Date: " << std::put_time(issueDate, "%Y-%m-%d") 
                    << ",Return Date: " << std::put_time(&returnDate, "%Y-%m-%d") << "\n";
            outFile.close();

            // Display borrowing information
            std::cout << "Book with ID " << bookId << " has been successfully borrowed.\n";
            std::cout << "Issue Date: " << std::put_time(issueDate, "%Y-%m-%d") << "\n";
            std::cout << "Return Date: " << std::put_time(&returnDate, "%Y-%m-%d") << "\n";
            std::cout << "Note: A fine of £1 will be applied for each day past the return date.\n";
            return true;
        } else {
            std::cerr << "Unable to open the file to record borrowing details." << std::endl;
            return false;
        }
    } else {
        std::cout << "No book found with ID " << bookId << ".\n";
        return false;
    }
}


void Book::displayAllBorrowedBooks() {
    std::ifstream inFile("borrow-book_details.txt");
    if (!inFile.is_open()) {
        std::cerr << "Could not open the borrow-book_details.txt file." << std::endl;
        return;
    }

    std::string line;
    std::cout << "List of all borrowed books:\n";
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    inFile.close();
}

void Book::displayBorrowedBooksByMemberId(int memberId) {
    std::ifstream inFile("borrow-book_details.txt");
    if (!inFile.is_open()) {
        std::cerr << "Failed to open borrow-book_details.txt" << std::endl;
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(inFile, line)) {
        if (line.find("Member ID: " + std::to_string(memberId)) != std::string::npos) {
            std::cout << line << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No borrowed books found for Member ID: " << memberId << std::endl;
    }

    inFile.close();
}
bool Book::returnBookById(int bookId, int memberId) {
    std::vector<std::string> records;
    std::ifstream inFile("borrow-book_details.txt");
    std::string line;
    bool isRecordFound = false;

    while (std::getline(inFile, line)) {
        std::string searchForMember = "Member ID: " + std::to_string(memberId);
        std::string searchForBook = "Book ID: " + std::to_string(bookId);
        
        // Check if both member ID and book ID are present in the line
        if (line.find(searchForMember) != std::string::npos && line.find(searchForBook) != std::string::npos) {
            isRecordFound = true; // Record to be removed found
        } else {
            records.push_back(line); // Keep all other records
        }
    }
    inFile.close();

    if (isRecordFound) {
        std::ofstream outFile("borrow-book_details.txt");
        for (const auto& record : records) {
            outFile << record << std::endl;
        }
        outFile.close();
        return true;
    } else {
        return false;
    }
}

void Book::calculateFine(int memberId) {
    std::ifstream inFile("borrow-book_details.txt");
    std::string line;
    int totalFine = 0;
    const int finePerDay = 1;  // Assuming £1 per day as fine

    auto now = std::chrono::system_clock::now();

    while (std::getline(inFile, line)) {
        if (line.find("Member ID: " + std::to_string(memberId)) != std::string::npos) {
            std::istringstream iss(line);
            std::string segment;
            std::vector<std::string> seglist;

            while (std::getline(iss, segment, ',')) {
                seglist.push_back(segment);
            }

            // Assuming the return date is the last segment
            std::string returnDateStr = seglist.back();
            returnDateStr = returnDateStr.substr(returnDateStr.find(":") + 2); // Extract date part

            std::tm returnDate = {};
            std::istringstream returnDateStream(returnDateStr);
            returnDateStream >> std::get_time(&returnDate, "%Y-%m-%d");

            // Convert returnDate to time_t for comparison
            std::time_t returnTime = std::mktime(&returnDate);
            auto returnTimePoint = std::chrono::system_clock::from_time_t(returnTime);

            if (now > returnTimePoint) {
                // Calculate the number of days late
                auto duration = std::chrono::duration_cast<std::chrono::hours>(now - returnTimePoint).count();
                int daysLate = duration / 24;
                totalFine += daysLate * finePerDay;
            }
        }
    }

    inFile.close();
    std::cout << "Total fine for Member ID " << memberId << " is: £" << totalFine << std::endl;
}
