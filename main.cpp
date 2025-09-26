#include <iostream>
using namespace std;

void showMenu() {
    cout << "=== Library Book System ===" << endl;
    cout << "1. View available books" << endl;
    cout << "2. Borrow a book" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    int option;
    bool running = true;

    while (running) {
        showMenu();
        cin >> option;

        switch (option) {
            case 1:
                cout << "Available books:" << endl;
                cout << "- The Great Gatsby" << endl;
                cout << "- 1984" << endl;
                cout << "- To Kill a Mockingbird" << endl;
                break;
            case 2:
                cout << "You borrowed a book. Enjoy your reading!" << endl;
                break;
            case 3:
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
