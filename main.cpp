#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

class Book {
private:
    string Title;
    string Author;
    string ISBN;
    bool   Availability;
    string DateAdd;

public:
    Book() : Title(""), Author(""), ISBN(""), Availability(true), DateAdd("") {}

    void setBookDetails(const string& t, const string& a, const string& i, const string& d) {
        Title = t; Author = a; ISBN = i; DateAdd = d; Availability = true;
    }

    void displayBookDetails() const {
        cout << "------------------------------\n";
        cout << "Title: " << Title << '\n';
        cout << "Author: " << Author << '\n';
        cout << "ISBN: " << ISBN << '\n';
        cout << "Date Added: " << DateAdd << '\n';
        cout << "Status: " << (Availability ? "Available" : "Borrowed") << '\n';
    }

    void borrowBook() {
        if (Availability) {
            Availability = false;
            cout << "Book reserved successfully.\n";
        }
        else {
            cout << "Error: Book is unavailable (already borrowed).\n";
        }
    }

    void returnBook() {
        if (!Availability) {
            Availability = true;
            cout << "Book returned successfully.\n";
        }
        else {
            cout << "Error: Book was not borrowed.\n";
        }
    }

    string getISBN()  const { return ISBN; }
    string getTitle() const { return Title; }
    bool   isAvailable() const { return Availability; }
    void   setAvailability(bool a) { Availability = a; }
};

static inline string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

string normalizeISBN(string s) {
    int i = 0;
    while (i < (int)s.size() && (s[i] == ' ' || s[i] == '0')) i++;
    string trimmed = s.substr(i);
    if (trimmed.empty()) return "0";
    if (trimmed.size() == 1 && isdigit(static_cast<unsigned char>(trimmed[0])) && trimmed[0] != '0') {
        return string("0") + trimmed;
    }
    return trimmed;
}

void sortBookData(Book books[], int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (books[i].getISBN() > books[j].getISBN())
                swap(books[i], books[j]);
}

void displayAllBooks(Book books[], int n) {
    int avail = 0, borrowed = 0;
    for (int i = 0; i < n; ++i) (books[i].isAvailable() ? ++avail : ++borrowed);
    cout << "\nLibrary Book System\n";
    cout << "[" << avail << " available | " << borrowed << " borrowed]\n";
    for (int i = 0; i < n; ++i) books[i].displayBookDetails();
}

void waitForEnter() {
    cout << "Press Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool borrowFlow(Book books[], int n) {
    string rawInput;
    cout << "Enter Title or ISBN to return. Enter 0 to cancel: ";
    getline(cin >> ws, rawInput);
    string input = normalizeISBN(rawInput);
    if (input == "0") return false;
    for (int i = 0; i < n; ++i) {
        if (books[i].getISBN() == input || toLower(books[i].getTitle()) == toLower(rawInput)) {
            books[i].borrowBook();
            waitForEnter();
            return true;
        }
    }
    cout << "Error: Book not found.\n";
    waitForEnter();
    return true;
}

bool returnFlow(Book books[], int n) {
    string rawInput;
    cout << "Enter Title or ISBN to return. Enter 0 to cancel: ";
    getline(cin >> ws, rawInput);
    if (rawInput == "0") { waitForEnter(); return true; }
    string input = normalizeISBN(rawInput);
    for (int i = 0; i < n; ++i) {
        if (books[i].getISBN() == input || toLower(books[i].getTitle()) == toLower(rawInput)) {
            books[i].returnBook();
            waitForEnter();
            return true;
        }
    }
    cout << "Error: Book not found.\n";
    waitForEnter();
    return true;
}

int main() {
    const int NUM_BOOKS = 5;
    Book books[NUM_BOOKS];
    books[0].setBookDetails("The Invention of Morel", "Adolfo Bioy Casares", "01", "2024-01-12");
    books[1].setBookDetails("Pedro Páramo", "Juan Rulfo", "02", "2023-12-01");
    books[2].setBookDetails("The Passion According to G.H.", "Clarice Lispector", "03", "2023-11-11");
    books[3].setBookDetails("The Tunnel", "Ernesto Sabato", "04", "2023-08-03");
    books[4].setBookDetails("Season of Migration to the North", "Tayeb Salih", "05", "2023-10-19");
    srand(static_cast<unsigned>(time(nullptr)));
    books[rand() % NUM_BOOKS].setAvailability(false);
    sortBookData(books, NUM_BOOKS);
    bool running = true;
    while (running) {
        sortBookData(books, NUM_BOOKS);
        displayAllBooks(books, NUM_BOOKS);
        cout << "\nMenu:\n";
        cout << "1. Borrow by Title or ISBN\n";
        cout << "2. Return by Title or ISBN\n";
        cout << "0. Exit\n";
        cout << "Enter option: ";
        int option;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Try again.\n\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (option) {
        case 1: running = borrowFlow(books, NUM_BOOKS); break;
        case 2: running = returnFlow(books, NUM_BOOKS); break;
        case 0: cout << "Exiting program. Goodbye!\n"; running = false; break;
        default: cout << "Invalid option. Try again.\n"; break;
        }
        cout << '\n';
    }
    return 0;
}

