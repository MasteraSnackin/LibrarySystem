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

Book book;

}
