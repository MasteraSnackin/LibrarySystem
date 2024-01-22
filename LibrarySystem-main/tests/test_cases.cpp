#include <catch2/catch.hpp>
#include "LibrarySystem-main/LibrarySystem.h"  // Include the correct relative path to your `LibrarySystem` header

TEST_CASE("Patron Creation", "[Patron]") {
Patron patron;
patron.name = "Jane Doe";
patron.id = 1;

REQUIRE(patron.name == "Jane Doe");
REQUIRE(patron.id == 1);
}

TEST_CASE("Book Adding", "[Book]") {
// Assuming your `Book` class has a method to set details and save to file
Book book;
// You would set details here, such as `book.setDetails("Book Title", "Author", 123);`
// Then check if the book details are correctly set
// REQUIRE(book.getTitle() == "Book Title");
// REQUIRE(book.getAuthor() == "Author");
// REQUIRE(book.getPageCount() == 123);

// If your `Book` class writes to a file, you can check the file contents as well
// std::ifstream file("path_to_book_file.csv");
// REQUIRE(file.good());
// std::string contents;
// std::getline(file, contents);
// REQUIRE(!contents.empty());
}

// Add more test cases for different functionalities of your LibrarySystem
