cmake_minimum_required(VERSION 3.14)
project(LibrarySystem)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for project header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the main application executable
add_executable(LibrarySystem LibrarySystem.cpp)
# If you have other cpp files, add them here as well

# Fetch Catch2 from GitHub
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x  # Use the appropriate tag for the version you want
)
FetchContent_MakeAvailable(Catch2)

# Create a tests directory if it does not exist
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)

# Specify the test files
set(TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_cases.cpp
)

# Add the test executable
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2)

# Enable testing with CTest
include(CTest)
enable_testing()

# Parse Catch tests and register them with CTest
Catch2_add_tests(
        tests
        TEST_PREFIX "catch2."
        TEST_LIST Catch2Tests
        SOURCES ${TEST_SOURCES}
)
