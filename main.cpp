/*
    Improvements Added:
    1. Added comments for each function for better organization and debugging
    2. Created new methods (functions) such as displayAvailableBooks() and borrowBook() for better organization

    Further Suggestions:
    1. Consider using O.O.P. (Object-Oriented Programming) classes for better code organization (best fitting for a library management system)
*/

#include <iostream>
using namespace std;

// [ METHOD ]: Display the main menu
void showMenu() {
    cout << "=== Library Book System ===" << endl;
    cout << "1. View available books" << endl;
    cout << "2. Borrow a book" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose an option: ";
}


// [ METHOD ]: Display the list of available books in the library
void displayAvailableBooks() {
    cout << "Available books:" << endl;
    // SUGGESTION: Create an array (a list of values) to store the list of available books instead of hard coding it
    cout << "- The Great Gatsby" << endl;
    cout << "- 1984" << endl;
    cout << "- To Kill a Mockingbird" << endl;
}

// [ METHOD ]: Borrow a book from the library
void borrowBook() {
    cout << "You borrowed a book. Enjoy your reading!" << endl;
    // Consider adding further implementations for borrowing a book...
}

int main() {
    int option;
    bool running = true;

    // This loop runs until the user chooses to exit the program
    while (running) {
        showMenu();
        cin >> option;

        // UPDATED: Moved case implementations inside new functions
        switch (option) {
            case 1:
                displayAvailableBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3: // Exit program
                cout << "Exiting program. Goodbye!" << endl;
                running = false;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
