#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H \
/*
LibrarySystem.h
Author: M00870488
Created: 1/7/2024
Updated: 22/1/2024
*/

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

class Book {
public:
    void addBook(const std::string& filePath);
};

class Patron {
public:
    std::string name;
    int id;
    std::set<int> borrowedBookIDs;

    Patron();
    void inputDetails();
};

class Library {
private:
    std::vector<Book> inventory;
    std::vector<Patron> patrons;
    std::string csvFilePath;
    std::string patronsFilePath;

public:
    Library();
    void start();
    int showMainMenu();
    void adminActions();
    void patronActions();
    void addBookToCSV();
    void addPatron();
    void listBooks();
    void listPatrons();
    void searchPatrons();
    void borrowBook();
    void returnBook();
    void searchBooks();
};

#endif // LIBRARYSYSTEM_H
