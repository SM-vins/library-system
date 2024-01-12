#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "book.h"
//test case for borrow book 
TEST_CASE("Book borrowing functionality", "[borrowBookById]") {
    SECTION("Borrowing a valid book") {
        int bookId = 1;
        int memberId = 1;
        REQUIRE(Book::borrowBookById(bookId, memberId) == true);
    }

    SECTION("Borrowing an invalid book") {
        int bookId = 2;
        int memberId = 1;
        REQUIRE(Book::borrowBookById(bookId, memberId) == false);
    }
}
//test case for return book
   
TEST_CASE("Book return functionality", "[returnBookById]") {
    SECTION("Returning a valid borrowed book") {
        int bookId = 1; 
        int memberId = 1; 
        REQUIRE(Book::returnBookById(bookId, memberId) == true);
    }

    SECTION("Returning a book not borrowed") {
        int bookId = 2;
        int memberId = 1;
        REQUIRE(Book::returnBookById(bookId, memberId) == false);
    }

    SECTION("Returning an invalid book") {
        int bookId = 9999; 
        int memberId = 1; 
        REQUIRE(Book::returnBookById(bookId, memberId) == false);
    }

}