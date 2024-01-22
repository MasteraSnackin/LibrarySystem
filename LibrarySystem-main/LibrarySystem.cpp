/*
LibrarySystem.cpp
Author: M00870488
Created: 1/7/2024
Updated: 22/1/2024
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// Class Book holds void addBook later used in admin menu
class Book {
public:

    // add book to the library_books.csv
    void addBook(const std::string& filePath) {
        std::ofstream file;
        file.open(filePath, std::ios::app); // Open in append mode
        if (file.is_open()) {
            int bookID, pageCount;
            std::string bookName, authorFirstName, authorLastName, bookType;

            std::cout << "Enter Book ID: ";
            std::cin >> bookID;
            std::cin.ignore(); // To clear the newline character from the buffer

            std::cout << "Enter Book Name: ";
            std::getline(std::cin, bookName); // Use getline to handle spaces

            std::cout << "Enter Page Count: ";
            std::cin >> pageCount;
            std::cin.ignore();

            std::cout << "Enter Author First Name: ";
            std::getline(std::cin, authorFirstName);

            std::cout << "Enter Author Last Name: ";
            std::getline(std::cin, authorLastName);

            std::cout << "Enter Book Type: ";
            std::getline(std::cin, bookType);

            // Writing to the CSV file
            file << bookID << "," << bookName << "," << pageCount << ","
                 << authorFirstName << "," << authorLastName << "," << bookType << "\n";
            file.close();
            std::cout << "Book details added to CSV.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

/* class Patron holds basic data about patron operations
such as addin new patron and their id*/
class Patron {
public:
    std::string name;
    int id;

    Patron() : name("Unknown"), id(-1) {}

    void inputDetails() {
        std::cout << "\nEnter Patron Nickname (without spaces): ";
        std::cin >> name;
        std::cout << "Enter Patron ID: ";
        std::cin >> id;
    }
};

/* class Library is Library system itself and provides
 * menu for authorized users to acces files such as
 * library_books.csv and Patrons.csv*/
class Library {
private:
    std::vector<Patron> patrons;

    // Strings holding paths to .csv files
    std::string csvFilePath = "LibrarySystem-main/library_books.csv";  // Update with the actual path
    std::string patronsFilePath = "Patrons.csv";

public:

    // Constructor
    void start() {
        int choice = showMainMenu();
        while (choice != 3) {
            if (choice == 1) {
                adminActions();
            } else if (choice == 2) {
                patronActions();
            }
            choice = showMainMenu();
        }
    }

    // User Interface
    int showMainMenu() {
        int choice;
        std::cout << "\n1) Admin\n2) Patron\n3) Exit\nChoose an option: ";
        std::cin >> choice;
        return (choice >= 1 && choice <= 3) ? choice : -1;
    }

    void adminActions() {
        int choice;
        std::cout << "\nAdmin Dashboard\n1) Add Book\n2) Add Patron\n"
                     "3) List Books\n4) List Patrons\n5) Search Patrons\n"
                     "6) Back\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addBookToCSV(); break;
            case 2: addPatron(); break;
            case 3: listBooks(); break;
            case 4: listPatrons(); break;
            case 5: searchPatrons(); break;
            case 6: return;
            default: std::cout << "Invalid choice, try again.\n";
        }
    }

    void patronActions() {
        int choice;
        std::cout << "\nPatron Dashboard\n1) Borrow Book\n"
                     "2) Return Book\n3) Search Books\n4) Back\n"
                     "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: borrowBook(); break;
            case 2: returnBook(); break;
            case 3: searchBooks(); break;
            case 4: return;
            default: std::cout << "Invalid choice, try again.\n";
        }
    }

    // Interacts with library_books.csv file through Book class
    void addBookToCSV() {
        Book newBook;
        newBook.addBook(csvFilePath);  // Utilize the new method from Book class
    }

    // Interacts with Patrons.csv file through Patron class
    void addPatron() {
        // Assuming a limit on the number of patrons
        if (patrons.size() >= 1000) {
            std::cout << "\nMaximum number of patrons reached.\n";
            return;
        }

        Patron newPatron;
        newPatron.inputDetails();

        // Open Patrons.csv in append mode
        std::ofstream outFile("Patrons.csv", std::ios::app);
        if (!outFile.is_open()) {
            std::cout << "Failed to open Patrons.csv for writing.\n";
            return;
        }

        // Write the new patron's details to the file
        outFile << newPatron.id << "," << newPatron.name << ",None\n";

        // Close the file
        outFile.close();

        // Add the patron to the in-memory list
        patrons.push_back(newPatron);

        std::cout << "File updated successfully." << std::endl;
    }

    // Show all available books in library
    void listBooks() {
        std::ifstream file(csvFilePath);

        if (!file.is_open()) {
            std::cout << "\nUnable to open the file.\n";
            return;
        }

        std::string line;
        std::cout << "\nList of Books:\n";
        std::cout << "ID, Name, Page Count, Author First Name,"
                     " Author Last Name, Book Type\n";

        while (std::getline(file, line)) {
            // Assuming the CSV format is: ID,Name,Page Count,Author First,Author Last,Type
            std::cout << line << std::endl;
        }

        file.close();
    }

    // Show all Patrons/Members of the library
    void listPatrons() {
        std::ifstream file(patronsFilePath);

        if (!file.is_open()) {
            std::cout << "\nUnable to open the file.\n";
            return;
        }

        std::string line;
        std::cout << "\nList of Patrons:\n";
        std::cout << "ID, Name, Borrowed Books\n";

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    }

    /* Open Patrons.csv and let user check if
     * person is member of the library */
    void searchPatrons() {
        std::string patronName;
        std::cout << "Enter Patron Name: ";
        std::cin >> patronName; // Using cin for user input

        std::ifstream file("Patrons.csv");
        std::string line;

        if (!file.is_open()) {
            std::cout << "Unable to open file" << std::endl;
            return;
        }

        bool found = false;
        while (std::getline(file, line)) {
            // Search for the patron name within each line
            if (line.find(patronName) != std::string::npos) {
                found = true;
                break;
            }
        }

        file.close();

        if (found) {
            std::cout << "Patron Name: " << patronName << " is included." << std::endl;
        } else {
            std::cout << "Patron not included." << std::endl;
        }
    }

    // Handles borrowing books through Patrons.csv
    void borrowBook() {
        std::string patronName, borrowedBook, date;
        std::cout << "Enter Patron Name: ";
        std::cin >> patronName;
        std::cout << "Enter Borrowed Book: ";
        std::cin >> borrowedBook;
        std::cout << "Enter Date (YYYY-MM-DD): ";
        std::cin >> date;

        std::ifstream inputFile("Patrons.csv");
        std::vector<std::string> lines;
        std::string line, modifiedLine;
        bool found = false;

        if (inputFile.is_open()) {
            while (std::getline(inputFile, line)) {
                std::stringstream ss(line);
                std::string id, name, book, existingDate;
                std::getline(ss, id, ',');
                std::getline(ss, name, ',');
                std::getline(ss, book, ',');
                std::getline(ss, existingDate, ',');

                if (name == patronName) {
                    modifiedLine = id + "," + name + "," + borrowedBook + "," + date;
                    lines.push_back(modifiedLine);
                    found = true;
                } else {
                    lines.push_back(line);
                }
            }
            inputFile.close();

            if (!found) {
                std::cout << "Patron not found." << std::endl;
                return;
            }

            std::ofstream outputFile("Patrons.csv");
            for (const auto &l : lines) {
                outputFile << l << std::endl;
            }
            outputFile.close();
            std::cout << "File updated successfully." << std::endl;
        } else {
            std::cout << "Error opening file." << std::endl;
        }
    }

    /* Same as borrowBook but will change column with
     * Borrowed Book to None*/
    void returnBook() {
        std::string patronName;
        std::string borrowedBook = "None";
        std::cout << "Enter Patron Name: ";
        std::cin >> patronName;

        std::ifstream inputFile("Patrons.csv");
        std::vector<std::string> lines;
        std::string line, modifiedLine;
        bool found = false;

        if (inputFile.is_open()) {
            while (std::getline(inputFile, line)) {
                std::stringstream ss(line);
                std::string id, name, book;
                std::getline(ss, id, ',');
                std::getline(ss, name, ',');
                std::getline(ss, book, ',');

                if (name == patronName) {
                    modifiedLine = id + "," + name + "," + borrowedBook;
                    lines.push_back(modifiedLine);
                    found = true;
                } else {
                    lines.push_back(line);
                }
            }
            inputFile.close();

            if (!found) {
                std::cout << "Patron not found." << std::endl;
                return;
            }

            std::ofstream outputFile("Patrons.csv");
            for (const auto &l : lines) {
                outputFile << l << std::endl;
            }
            outputFile.close();
            std::cout << "Book returned.\nFile updated successfully." << std::endl;
        } else {
            std::cout << "Error opening file." << std::endl;
        }
    }

    // Let user find search specific books from library
    void searchBooks() {
        std::ifstream file(csvFilePath);
        if (!file.is_open()) {
            std::cout << "\nUnable to open the file.\n";
            return;
        }

        std::string searchTerm;
        std::cout << "Enter Book Name: ";
        std::cin.ignore(); // To handle the newline character
        std::getline(std::cin, searchTerm); // To read the full title

        std::string line;
        bool found = false;
        std::cout << "\nSearch Results:\n";

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> bookDetails;

            while (std::getline(ss, item, ',')) {
                bookDetails.push_back(item);
            }

            if (bookDetails.size() >= 2 && bookDetails[1].find(searchTerm) != std::string::npos) {
                std::cout << "Book is available.\n";
                std::cout << "Book ID: " << bookDetails[0] << ", Book Name: " << bookDetails[1]
                          << ", Page Count: " << bookDetails[2] << ", Author First Name: " << bookDetails[3]
                          << ", Author Last Name: " << bookDetails[4] << ", Book Type: " << bookDetails[5] << std::endl;
                found = true;
                break; // Break the loop once the book is found
            }
        }

        if (!found) {
            std::cout << "No books found matching the search term.\n";
        }

        file.close();
    }
};

/* Starts the program using constructor
 * C++ naturaly looks for main function */
int main() {
    Library myLibrary;
    myLibrary.start();
    return 0;
}
