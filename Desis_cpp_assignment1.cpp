#include <bits/stdc++.h>
using namespace std;

class Person{ //base class 'person' shows abstraction and encapsulation
private:
    string name; //encapsulation: private data members
    int id;
public:
    Person(string n, int i){ //constructor
        name = n;
        id = i;
    }

    void set_name(string n){ //setter methods --> encapsulation is controlled access
        name = n;
    }

    void set_id(int i){
        id = i;
    }

    int get_id(){ //getter methods
        return id;
    }

    string get_name(){
        return name;
    }

    virtual void DisplayDetails() = 0; //pure virtual function --> polymorphism
};

class StoreManager : public Person{ //derived class uses inheritance and polymorphism
public:
    StoreManager(string n, int i) : Person(n, i) {} //constructor

    void DisplayDetails() override{ //overriding the virtual function
        cout << "Name of the store manager: " << get_name() << " and their ID is: " << get_id() << endl;
    }
};

class Cashier : public Person{
public:
    Cashier(string n, int i) : Person(n, i) {}

    void DisplayDetails() override{
        cout << "Name of the cashier: " << get_name() << " and their ID is: " << get_id() << endl;
    }
};

class Customer : public Person{
public:
    Customer(string n, int i) : Person(n, i) {}

    void DisplayDetails() override{
        cout << "Name of the customer: " << get_name() << " and their ID is: " << get_id() << endl;
    }
};

class Book{
private:
    string title;
    string author;
    int book_id;
    int number_of_copies;
    double cost_price; // price when bought
    double selling_price; // price at which sold the book

public:
    Book(string t, string a, int id, int noc, double cp, double sp){
        title = t;
        author = a;
        book_id = id;
        number_of_copies = noc;
        cost_price = cp;
        selling_price = sp;
    }

    string get_title(){
        return title;
    }

    string get_author(){
        return author;
    }

    int get_book_id(){
        return book_id;
    }

    int get_no_of_copies(){
        return number_of_copies;
    }

    int get_price(){
        return selling_price;
    }

    void add_stock(int quantity){
        number_of_copies += quantity;
    }

    // void sell_book(int quantity){
    //     if(quantity > number_of_copies) cout << "Number of copies available less than what you want. Number of copies available are: " << number_of_copies << ". Thanks!" << endl;
    //     else number_of_copies -= quantity;
    //     return;
    // }

    bool sell_book(int quantity){ // this is boolean because we are using a check condition in a method below using this
        if(quantity > number_of_copies){
            cout << "Number of copies available less than what you want. Number of copies available are: " << number_of_copies << ". Thanks!" << endl;
            return false;
        }
        else{
            number_of_copies -= quantity;
            return true;
        }
    }

    void display_book_details(){
        cout << "Title of the book: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Book ID: " << book_id << endl;
        cout << "Copies available: " << number_of_copies << endl;
        cout << "Price per copy: " << selling_price << endl;
        cout << endl;
    }
};

class Inventory{ // inventory class is a collection of Book objects --> composition
private:
    vector<Book> books;
public:
    void addBook(Book &book){ //adding a book to inventory
        books.push_back(book);
    }

    void display_Inventory(){ // display all books in inventory
        int count = 1;
        for(auto book : books){
            cout << count << "." << endl;
            book.display_book_details();
            count++;
        }
    }

    Book* find_book_by_book_id(int id){ //search for book by book_id
        for(auto &book : books){
            if(book.get_book_id() == id) return &book;
        }
        return nullptr;
    }

    Book* find_book_by_title(string name){ //search for book by title of the book
        for(auto &book : books){
            if(book.get_title() == name) return &book;
        }
        return nullptr;
    }

    void display_books_within_budget(int budget){ //search for books within your budget
        if(books.empty()){
            cout << "No books in inventory." << endl;
        }
        int count = 1, i = 0;
        for(auto &book : books){
            if(book.get_price() <= budget){
                cout << count << "." << endl;
                book.display_book_details();
                count++;
                i++;
            }
        }
        if(i > 0) cout << "You can select from these books. Thanks!" << endl;
        else cout << "No books available with price within the given budget." << endl;
        return;
    }
};

class BookStore{ //overall bookstore, managing everything
private:
    Inventory inventory; //composiion: 'inventory' is a part of 'bookstore'
    StoreManager manager;
    Cashier cashier;
public:
    BookStore(string manager_name, int manager_id, string cashier_name, int cashier_id)
    : manager(manager_name, manager_id), cashier(cashier_name, cashier_id) {}

    void add_book_to_inventory(Book book){
        Book* existing_book = inventory.find_book_by_book_id(book.get_book_id());
        if(existing_book){
            existing_book->add_stock(book.get_no_of_copies());
            cout << "Updated stock for book: " << book.get_title() << endl;
        }
        else{
            inventory.addBook(book);
            cout << "Book added successfully!" << endl;
        }
    }

    void display_inventory(){
        inventory.display_Inventory();
    }

    Book* find_book_by_title(string name){
        return inventory.find_book_by_title(name);
    }

    Book* find_book_by_id(int id){
        return inventory.find_book_by_book_id(id);
    }

    void display_books_within_budget(int budget){
        inventory.display_books_within_budget(budget);
    }

    void sell_book_by_id(int id, int quantity){
        Book *book = inventory.find_book_by_book_id(id);
        if(book){
            // if(book->get_no_of_copies() == 0) cout << "Not available. Sorry!" << endl;
            if(book->sell_book(quantity)){
                cout << "Sold " << quantity << " copies of " << book->get_title() << "." << endl;
            }
        }
        else cout << "Book with book ID: " << id << " not found!" << endl;
    }

    void sell_book_by_title(string name, int quantity){
        Book *book = inventory.find_book_by_title(name);
        if(book){
            // if(book->get_no_of_copies() == 0) cout << "Not available. Sorry!" << endl;
            if(book->sell_book(quantity)){
                cout << "Sold " << quantity << " copies of " << book->get_title() << "." << endl;
            }
        }
        else cout << "Book with title: " << name << " not found!" << endl;
    }

    void restock_book(int id, int quantity){
        Book *book = inventory.find_book_by_book_id(id);
        if(book){
            book->add_stock(quantity);
            cout << "Restocked " << quantity << " copies of the book." << endl;
        }
        else cout << "Book with book ID: " << id << " not found!" << endl;
    }

    void display_staff_details(){
        manager.DisplayDetails();
        cashier.DisplayDetails();
    }
};

int main(){ 
    //implemented the main function in a menu format for better user interaction
    BookStore bookstore("Manager1", 1, "Cashier1", 2);

    //Adding some initial books to the inventory
    bookstore.add_book_to_inventory(Book("Harry Potter", "J.K.Rowling", 1, 10, 200, 300));
    bookstore.add_book_to_inventory(Book("Percy Jackson", "Rick Riordan", 2, 15, 150, 250));
    bookstore.add_book_to_inventory(Book("Lord of the rings", "J.R.R.Tolkien", 3, 20, 180, 280));

    int choice;

    do {
        cout << "Welcome to the Bookstore! Please enter who you are:" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Cashier" << endl;
        cout << "3. Manager" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1){ // Customer menu
            int customer;
            do{
                cout << "Customer Menu:" << endl;
                cout << "1. View all books available" << endl;
                cout << "2. Search book by name" << endl;
                cout << "3. Search book by book ID" << endl;
                cout << "4. Search books within your budget" << endl;
                cout << "5. Buy a book" << endl;
                cout << "6. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> customer;

                switch(customer){
                case 1:
                    bookstore.display_inventory();
                    break;
                case 2:{
                    string name;
                    cout << "Enter the book name: ";
                    cin.ignore();
                    getline(cin, name);
                    Book* book = bookstore.find_book_by_title(name);
                    if(book) book->display_book_details();
                    else cout << "Book not found!" << endl;
                    break;
                }
                case 3:{
                    int id;
                    cout << "Enter the book ID: ";
                    cin >> id;
                    Book* book = bookstore.find_book_by_id(id);
                    if(book) book->display_book_details();
                    else cout << "Book not found!" << endl;
                    break;
                }
                case 4:{
                    int budget;
                    cout << "Enter your budget: ";
                    cin >> budget;
                    bookstore.display_books_within_budget(budget);
                    break;
                }
                case 5:{
                    int id, quantity;
                    cout << "Enter the book ID: ";
                    cin >> id;
                    if(bookstore.find_book_by_id(id)->get_no_of_copies() == 0) cout << "Not available. Sorry!" << endl;
                    else{
                        cout << "Enter the quantity: ";
                        cin >> quantity;
                        bookstore.sell_book_by_id(id, quantity);
                        break;
                    }
                }
                case 6:
                    cout << "Exiting Customer Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }while(customer != 6);
        }
        else if(choice == 2){ // Cashier menu
            int cashier;
            do{
                cout << "Cashier Menu:" << endl;
                cout << "1. View all books available" << endl;
                cout << "2. Sell a book by ID" << endl;
                cout << "3. Restock a book" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> cashier;

                switch(cashier){
                case 1:
                    bookstore.display_inventory();
                    break;
                case 2:{
                    int id, quantity;
                    cout << "Enter the book ID: ";
                    cin >> id;
                    cout << "Enter the quantity: ";
                    cin >> quantity;
                    bookstore.sell_book_by_id(id, quantity);
                    break;
                }
                case 3:{
                    int id, quantity;
                    cout << "Enter the book ID: ";
                    cin >> id;
                    cout << "Enter the quantity to restock: ";
                    cin >> quantity;
                    bookstore.restock_book(id, quantity);
                    break;
                }
                case 4:
                    cout << "Exiting Cashier Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }while(cashier != 4);
        }
        else if(choice == 3){ // Manager menu
            int manager;
            do{
                cout << "Manager Menu:" << endl;
                cout << "1. View all books available" << endl;
                cout << "2. Add a new book to inventory" << endl;
                cout << "3. View staff details" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> manager;

                switch(manager){
                case 1:
                    bookstore.display_inventory();
                    break;
                case 2:{
                    string title, author;
                    int id, copies;
                    double costPrice, sellingPrice;
                    cout << "Enter book ID: ";
                    cin >> id;
                    cout << "Enter book title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter book author: ";
                    getline(cin, author);
                    cout << "Enter number of copies: ";
                    cin >> copies;
                    cout << "Enter cost price: ";
                    cin >> costPrice;
                    cout << "Enter selling price: ";
                    cin >> sellingPrice;
                    bookstore.add_book_to_inventory(Book(title, author, id, copies, costPrice, sellingPrice));
                    cout << "Book added successfully!" << endl;
                    break; 
                }
                case 3:
                    bookstore.display_staff_details();
                    break;
                case 4:
                    cout << "Exiting Manager Menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }while(manager != 4);
        }
        else if(choice == 4) cout << "Thank you for visiting the bookstore!" << endl;
        else cout << "Invalid choice. Try again." << endl;
    }while(choice != 4);

    return 0;
}